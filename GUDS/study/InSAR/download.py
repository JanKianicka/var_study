import os
from datetime import date, timedelta
import requests
import pandas as pd
import geopandas as gpd
from shapely.geometry import shape

copernicus_user = os.getenv("copernicus_user") # copernicus User
copernicus_password = os.getenv("copernicus_password") # copernicus Password
ft = "POLYGON((48.9 18.1, 48.5 18.1, 48.5 18.9, 48.9 18.9, 48.9 18.1))"  # WKT Representation of BBOX
data_collection = "SENTINEL-1" # Sentinel satellite

today =  date.today()
today_string = today.strftime("%Y-%m-%d")
yesterday = today - timedelta(days=1)
yesterday_string = yesterday.strftime("%Y-%m-%d")



def get_keycloak(username: str, password: str) -> str:
    data = {
        "client_id": "cdse-public",
        "username": username,
        "password": password,
        "grant_type": "password",
    }
    try:
        r = requests.post(
            "https://identity.dataspace.copernicus.eu/auth/realms/CDSE/protocol/openid-connect/token",
            data=data,
        )
        r.raise_for_status()
    except Exception as e:
        raise Exception(
            f"Keycloak token creation failed. Reponse from the server was: {r.json()}"
        )
    return r.json()["access_token"]


# json = requests.get("https://catalogue.dataspace.copernicus.eu/odata/v1/Products?$filter=Collection/Name eq '{data_collection}' and OData.CSC.Intersects(area=geography'SRID=4326;{ft}') and ContentDate/Start gt {yesterday_string}T00:00:00.000Z and ContentDate/Start lt {today_string}T00:00:00.000Z&$count=True&$top=1000").json()

# The original request for Sentinel2 data from the example - Instanbul
#json = requests.get("https://catalogue.dataspace.copernicus.eu/odata/v1/Products?$filter=OData.CSC.Intersects(area=geography'SRID=4326;POLYGON((12.655118166047592 47.44667197521409,21.39065656328509 48.347694733853245,28.334291357162826 41.877123516783655,17.47086198383573 40.35854475076158,12.655118166047592 47.44667197521409))') and ContentDate/Start gt 2022-05-20T00:00:00.000Z and ContentDate/Start lt 2022-05-21T00:00:00.000Z").json()

# BBOX
# 18.50 48.49, 18.47 48.80, 19.03 48.81, 19.03 48.42

#json = requests.get("https://catalogue.dataspace.copernicus.eu/odata/v1/Products?$filter=Collection/Name eq 'SENTINEL-1' and contains(Name,'SLC') and contains(Name,'F8A7') and Attributes/OData.CSC.StringAttribute/any(att:att/Name eq 'orbitDirection' and att/OData.CSC.StringAttribute/Value eq 'DESCENDING') and OData.CSC.Intersects(area=geography'SRID=4326;POLYGON((18.50 48.49, 18.47 48.80, 19.03 48.81, 19.03 48.42, 18.50 48.49))') and ContentDate/Start gt 2023-12-01T00:00:00.000Z and ContentDate/Start lt 2023-12-10T00:00:00.000Z").json()

json = requests.get("https://catalogue.dataspace.copernicus.eu/odata/v1/Products?$filter=Collection/Name eq 'SENTINEL-1' and contains(Name,'SLC') and Attributes/OData.CSC.StringAttribute/any(att:att/Name eq 'orbitDirection' and att/OData.CSC.StringAttribute/Value eq 'DESCENDING') and OData.CSC.Intersects(area=geography'SRID=4326;POLYGON((19.14 48.63, 19.14 48.64, 19.15 48.64, 19.15 48.63, 19.14 48.63))') and ContentDate/Start gt 2020-08-01T00:00:00.000Z and ContentDate/Start lt 2020-12-31T23:59:59.000Z").json()

print(json)
p = pd.DataFrame.from_dict(json["value"]) # Fetch available dataset
print(p)
if p.shape[0] > 0 :
    p["geometry"] = p["GeoFootprint"].apply(shape)
    productDF = gpd.GeoDataFrame(p).set_geometry("geometry") # Convert PD to GPD
    #productDF = productDF[~productDF["Name"].str.contains("L1C")] # Remove L1C dataset
    print(f" total SLC tiles found {len(productDF)}")
    productDF["identifier"] = productDF["Name"].str.split(".").str[0]
    allfeat = len(productDF)

    #keycloak_token = get_keycloak(copernicus_user,copernicus_password)
    #print("KEYCLOAK")
    #session = requests.Session()
    #print("session")
    #session.headers.update({"Authorization": f"Bearer {keycloak_token}"})
    
    if allfeat == 0:
        print("No tiles found for today")
    else:
        ## download all tiles from server
        for index,feat in enumerate(productDF.iterfeatures()):
            try:
                #keycloak_token = get_keycloak(copernicus_user,copernicus_password)
                #print("KEYCLOAK")
                #session.headers.update({"Authorization": f"Bearer {keycloak_token}"})
                #url = f"https://catalogue.dataspace.copernicus.eu/odata/v1/Products({feat['properties']['Id']})/$value"
                #response = session.get(url, allow_redirects=False, stream=True)
                
                # check for existence of the file
                out_f = f"{feat['properties']['identifier']}.zip"
                if os.path.isfile(f"{out_f}"):
                    print("%s exists"% out_f)
                else:
                    print("%s does not exists - downloading" % out_f)
                    #continue
                    session = requests.Session()
                    
                    keycloak_token = get_keycloak(copernicus_user,copernicus_password)
                    print("KEYCLOAK")
                    session.headers.update({"Authorization": f"Bearer {keycloak_token}"})
                    
                    url = f"https://catalogue.dataspace.copernicus.eu/odata/v1/Products({feat['properties']['Id']})/$value"
                    response = session.get(url, allow_redirects=False, stream=True)
                    print("Response")
                    
                    while response.status_code in (301, 302, 303, 307):
                        url = response.headers["Location"]
                        response = session.get(url, allow_redirects=False)
                    print(feat["properties"]["Id"])
                    #file = session.get(url, verify=True, allow_redirects=True)
                    with open(f"{feat['properties']['identifier']}.zip","wb") as p:
                        for chunk in response.iter_content(chunk_size=8192):
                            if chunk:
                                p.write(chunk)

                    session.close()
                    print("Session closed")
                    
#                with open(
#                    f"{feat['properties']['identifier']}.zip", #location to save zip from copernicus 
#                    "wb",
#                ) as p:
#                    print(feat["properties"]["Name"])
#                    p.write(file.content)
            except:
                print("problem with server")
else :
    print('no data found')
