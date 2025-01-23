import configparser
import os
import sys

# CONSTANTS
ODATA_SERVICE_URL = '"https://catalogue.dataspace.copernicus.eu/odata/v1/Products'
FILTER_COLLECTION_NAME = 'Collection/Name eq %s'
FILTER_CONTAINS_NAME = 'contains(Name,%s)'
FILTER_ATT_ORBIT_DIRECTION = 'Attributes/OData.CSC.StringAttribute/any(att:att/Name eq \'orbitDirection\' and att/OData.CSC.StringAttribute/Value eq %s)'
FILTER_ATT_REL_ORBIT_NUM = 'Attributes/OData.CSC.IntegerAttribute/any(att:att/Name eq \'relativeOrbitNumber\' and att/OData.CSC.IntegerAttribute/Value eq %s)'
FILTER_ATT_SLICE_NUM = 'Attributes/OData.CSC.IntegerAttribute/any(att:att/Name eq \'sliceNumber\' and att/OData.CSC.IntegerAttribute/Value eq %s)'
FILTER_ATT_CONT_DATE_START = 'ContentDate/Start gt %s'
FILTER_ATT_CONT_DATE_END = 'ContentDate/Start lt %s'

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
    else:
        print("Not parsed config key", key)
    
print(ODATA_QUERY)


