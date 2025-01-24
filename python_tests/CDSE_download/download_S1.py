'''
    download_S1.py is the script for downloading 
    primary Sentinel1 data from OData Copernicus Data Service.
    It is designed to download based on 
    - Collection name
    - contains attribute in the product name which filters the level of processing
    - orbit direction
    - relative orbit number
    - slice number
    - data start, date end
    
    Initial version:
        Jan Kianicka, January 2025
    TODO:
    - check env. variables for credentials
    - handle better exceptions
    - check md5 hash codes 
    - retry in case of failure
    - fill in missing data
    - add ordering in the query
     
'''
import configparser
import os
import requests
import sys
import time

# CONSTANTS
ODATA_SERVICE_URL = 'https://catalogue.dataspace.copernicus.eu/odata/v1/Products'
FILTER_COLLECTION_NAME = 'Collection/Name eq %s'
FILTER_CONTAINS_NAME = 'contains(Name,%s)'
FILTER_ATT_ORBIT_DIRECTION = 'Attributes/OData.CSC.StringAttribute/any(att:att/Name eq \'orbitDirection\' and att/OData.CSC.StringAttribute/Value eq %s)'
FILTER_ATT_REL_ORBIT_NUM = 'Attributes/OData.CSC.IntegerAttribute/any(att:att/Name eq \'relativeOrbitNumber\' and att/OData.CSC.IntegerAttribute/Value eq %s)'
FILTER_ATT_SLICE_NUM = 'Attributes/OData.CSC.IntegerAttribute/any(att:att/Name eq \'sliceNumber\' and att/OData.CSC.IntegerAttribute/Value eq %s)'
FILTER_ATT_CONT_DATE_START = 'ContentDate/Start gt %s'
FILTER_ATT_CONT_DATE_END = 'ContentDate/Start lt %s'

ODATA_SERVICE_TOKEN_URL = 'https://identity.dataspace.copernicus.eu/auth/realms/CDSE/protocol/openid-connect/token'
ODATA_DOWNLOAD_SERVICE_URL = 'https://download.dataspace.copernicus.eu/odata/v1/Products(%s)/$value'

copernicus_user = os.getenv("copernicus_user") # copernicus User
copernicus_password = os.getenv("copernicus_password") # copernicus Password

print ("Commencing Sentinel-1 data download from OData Web service of CDSE")
print ("Reading parameter file: ", sys.argv[1])

config = configparser.ConfigParser()
config.read(sys.argv[1])

print(config.sections())

ODATA_QUERY = ''
ODATA_QUERY = ODATA_QUERY + ODATA_SERVICE_URL + '?$filter='

# parsing the config file
for key in config['S1 donwload pars']:
    print(' ', key, ":", config['S1 donwload pars'][key])
    if key == 'collection_name':
        filter_collection_name = (FILTER_COLLECTION_NAME%config['S1 donwload pars'][key])
        ODATA_QUERY = ODATA_QUERY + filter_collection_name
    elif key == 'contains_name':
        filter_contains_name = (FILTER_CONTAINS_NAME%config['S1 donwload pars'][key])
        ODATA_QUERY = ODATA_QUERY + ' and ' + filter_contains_name
    elif key == 'orbit_direction':
        filter_orbit_direction = (FILTER_ATT_ORBIT_DIRECTION%config['S1 donwload pars'][key])
        ODATA_QUERY = ODATA_QUERY + ' and ' + filter_orbit_direction
    elif key == 'rel_orbit_num':
        filer_rel_orbit_num = (FILTER_ATT_REL_ORBIT_NUM%config['S1 donwload pars'][key])
        ODATA_QUERY = ODATA_QUERY + ' and ' + filer_rel_orbit_num
    elif key == 'slice_num':
        filter_slice_num = (FILTER_ATT_SLICE_NUM%config['S1 donwload pars'][key])
        ODATA_QUERY = ODATA_QUERY + ' and ' + filter_slice_num
    elif key == 'cont_date_start':
        filter_cont_date_start = (FILTER_ATT_CONT_DATE_START%config['S1 donwload pars'][key])
        ODATA_QUERY = ODATA_QUERY + ' and ' + filter_cont_date_start
    elif key == 'cont_date_end':
        filter_cont_date_end = (FILTER_ATT_CONT_DATE_END%config['S1 donwload pars'][key])
        ODATA_QUERY = ODATA_QUERY + ' and ' + filter_cont_date_end
    elif key == 'target_dir':
        TARGET_BASE_DIR = config['S1 donwload pars'][key]
    else:
        print("Not parsed config key", key)

# Connection token
post_data = {
    "client_id": "cdse-public",
    "username": copernicus_user,
    "password": copernicus_password,
    "grant_type": "password",
}
def getToken():
    r = requests.post(
            ODATA_SERVICE_TOKEN_URL,
            data = post_data
        )

    token = r.json()['access_token']
    return token
  
print("Search data query: ", ODATA_QUERY)
json = requests.get(ODATA_QUERY).json()
productList = json['value']


print("Number of found scenes to download: ", len(productList))
wStart = time.time()

for scene in productList:
    sceneName = scene.get('Name')
    sceneId = scene.get('Id')
    targetFile = os.path.join(TARGET_BASE_DIR.strip('\''), sceneName.replace('SAFE', 'zip'))
    if os.path.isfile(f"{targetFile}"):
        print("%s exists"% targetFile)
    else:
        download_URL = (ODATA_DOWNLOAD_SERVICE_URL%sceneId)
        print('Small break')
        time.sleep(30)
        
        print('Starting downloading product: ', sceneName)
        print(download_URL)
        token = getToken()
        print("Generated authorization token ", token[:10], '...', token[-10:])
        
        start = time.time()
        headers = {"Authorization": f"Bearer {token}"}
    
        # Create a session and update headers
        session = requests.Session()
        session.headers.update(headers)
    
        # Perform the GET request
        response = session.get(download_URL, stream=True)
    
        # Check if the request was successful
        if response.status_code == 200:
            with open(targetFile, "wb") as file:
                for chunk in response.iter_content(chunk_size=8192):
                    if chunk:  # filter out keep-alive new chunks
                        file.write(chunk)
        else:
            print(f"Failed to download file. Status code: {response.status_code}")
            print(response.text)
        
        print(sceneName + " successfully downloaded")
        session.close()
        end = time.time()
        print('Elapsed time', '%.2f'%((end - start)/60) + ' min')
wEnd = time.time()
print('Successfully finished whole processing in ', '%.2f'%((wEnd - wStart)/60) + ' min')