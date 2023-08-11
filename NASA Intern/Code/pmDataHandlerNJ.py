# -*- coding: utf-8 -*- 

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


PA_25_PATHS = [r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM2.5/New Jersey/2017_nj.csv",
            r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM2.5/New Jersey/2018_nj.csv",
            r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM2.5/New Jersey/2019_nj.csv",
            r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM2.5/New Jersey/2020_nj.csv",
            r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM2.5/New Jersey/2021_nj.csv"]

PA_10_PATHS = [r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM10/New Jersey/2017_nj.csv",
            r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM10/New Jersey/2018_nj.csv",
            r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM10/New Jersey/2019_nj.csv",
            r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM10/New Jersey/2020_nj.csv",
            r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM10/New Jersey/2021_nj.csv"]

DROP_COLS = ["Source", "POC", "DAILY_AQI_VALUE",
             "DAILY_OBS_COUNT", "PERCENT_COMPLETE",
             "AQS_PARAMETER_DESC", "CBSA_CODE", "CBSA_NAME",
             "STATE_CODE", "COUNTY_CODE",
             "SITE_LATITUDE", "SITE_LONGITUDE"]

COUNTIES = []





if __name__ == "__main__":
    
    
    dataFile = pd.read_csv(PA_25_PATHS[0])
    dataFile.drop(columns=DROP_COLS, inplace=True)
    
    for row in range(len(dataFile)):
        if dataFile.loc[row, 'COUNTY'] not in COUNTIES:
            COUNTIES.append(dataFile.loc[row, 'COUNTY'])
    
    dataFile = pd.read_csv(PA_10_PATHS[0])
    dataFile.drop(columns=DROP_COLS, inplace=True)
    
    for row in range(len(dataFile)):
        if dataFile.loc[row, 'COUNTY'] not in COUNTIES:
            COUNTIES.append(dataFile.loc[row, 'COUNTY'])
            
    
    
    
    for county in COUNTIES:
        #dataFile = pd.read_csv(PA_25_PATHS[0])
        yearNum = 2017
        
        for year in PA_25_PATHS:
            dataFile = pd.read_csv(year)
            dataFile.drop(columns=DROP_COLS, inplace=True)
            
            #dont permanently mute this variable anymore

            theCounty = dataFile[dataFile.COUNTY == county]
            
            theCounty['Datetime'] =  pd.to_datetime(theCounty['Date'], format='%m/%d/%Y')
            theCounty.set_index('Datetime', inplace=True)

            theCounty = theCounty.resample('M').mean()

            
            if len(theCounty) > 2:
                plt.figure(figsize=(15,10))
                plt.xticks(rotation=70)
                plt.plot(theCounty.index[::1], theCounty["Daily Mean PM2.5 Concentration"].iloc[::1])
                # overlay with proper dates in ppt
                
                plt.title(str(yearNum) + " PM2.5 Concentration in " + county + " County, NJ")
                plt.xlabel("Date")
                plt.ylabel("Monthly Mean PM2.5 Concentration (ug/m3 LC)")
                plt.show()
                yearNum += 1
            
                   
        yearNum = 2017
            
        for year in PA_10_PATHS:
            dataFile = pd.read_csv(year)
            dataFile.drop(columns=DROP_COLS, inplace=True)
            
            #dont permanently mute this variable anymore 
        
            theCounty = dataFile[dataFile.COUNTY == county]
            theCounty['Datetime'] =  pd.to_datetime(theCounty['Date'], format='%m/%d/%Y')
            theCounty.set_index('Datetime', inplace=True)
            
            
            theCounty = theCounty.resample('M').mean()
            

            if len(theCounty) > 2:
                plt.figure(figsize=(15,10))
                plt.xticks(rotation=70)
                plt.plot(theCounty.index[::1], theCounty["Daily Mean PM10 Concentration"].iloc[::1])
                # overlay with proper dates in ppt
                
                plt.title(str(yearNum) + " PM10 Concentration in " + county + " County, NJ")
                plt.xlabel("Date")
                plt.ylabel("Monthly Mean PM10 Concentration (ug/m3 SC)")
                plt.show()
                yearNum += 1
        
        
        
        
        
      