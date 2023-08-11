# -*- coding: utf-8 ,-)*-
"""
Spyder Editor

This is a temporary script file.
"""


# Import the geopandas and geoplot libraries
import geopandas as gpd
import pandas as pd
import matplotlib.pyplot as plt
import plotly.express as px




PA_25_PATHS = [r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM2.5/Maryland/2021_md.csv"]#, r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM2.5/New York/2021_ny.csv"]#, r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM2.5/New Jersey/2021_nj.csv"]
KEEP_STATES = ['24']#['42', '36', '24']#, '34']



# Load the json file with county coordinates

for i in range(len(PA_25_PATHS)):
        
    geoData = gpd.read_file('https://raw.githubusercontent.com/holtzy/The-Python-Graph-Gallery/master/static/data/US-counties.geojson')
    dataFile = pd.read_csv(PA_25_PATHS[i])
    dataFile_geo = gpd.GeoDataFrame(dataFile, geometry=gpd.points_from_xy(dataFile.SITE_LONGITUDE, dataFile.SITE_LATITUDE))
    # Make sure the "id" column is an integer
    geoData.id = geoData.id.astype(str).astype(int)
    
    stateToKeep = [KEEP_STATES[i]] #pa, ny, nj
    geoData = geoData[geoData.STATE.isin(stateToKeep)]
    
    axis = geoData[geoData.STATE.isin(stateToKeep)].plot(color='lightyellow', edgecolor='black')
    
    dataFile_geo.plot(ax=axis, color='red')
    fig=plt.gcf()
    fig.set_size_inches(15,25)
    plt.show()





"""
fig=plt.gcf()
fig.set_size_inches(10,8)
plt.show()
"""
"""
fig = px.choropleth(dataFile_geo, geojson=dataFile_geo.geometry, locations=dataFile.index, projection="mercator")
fig.update_geos(fitbounds="locations", visible=False)
fig.show()

"""


#geoData.plot()