# -*- coding: utf-8 -*- 

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


PA_25_PATHS = [r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM2.5/Maryland/2017_md.csv",
            r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM2.5/Maryland/2018_md.csv",
            r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM2.5/Maryland/2019_md.csv",
            r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM2.5/Maryland/2020_md.csv",
            r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM2.5/Maryland/2021_md.csv"]

PA_10_PATHS = [r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM10/Maryland/2017_md.csv",
            r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM10/Maryland/2018_md.csv",
            r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM10/Maryland/2019_md.csv",
            r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM10/Maryland/2020_md.csv",
            r"/home/eric/Documents/SaSa/Reseach Project/Datasets/PM10/Maryland/2021_md.csv"]

DROP_COLS = ["Source", "POC", "DAILY_AQI_VALUE",
             "DAILY_OBS_COUNT", "PERCENT_COMPLETE",
             "AQS_PARAMETER_DESC", "CBSA_CODE", "CBSA_NAME",
             "STATE_CODE", "COUNTY_CODE",
             "SITE_LATITUDE", "SITE_LONGITUDE"]

# global variable
COUNTIES = ["Baltimore (City)"]#, "Baltimore (City)"]
funcCOUNTIES = ["Baltimore (City)"]

def BaltCo():
    for county in funcCOUNTIES:
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
                plt.figure(figsize=(10,5))
                plt.xticks(rotation=70)
                plt.plot(theCounty.index[::1], theCounty["Daily Mean PM2.5 Concentration"].iloc[::1])
                # overlay with proper dates in ppt
                
                plt.title(str(yearNum) + " PM2.5 Concentration in " + county + " County, MD")
                plt.xlabel("Date")
                plt.ylabel("Monthly Mean PM2.5 Concentration (ug/m3 LC)")
                plt.show()
                yearNum += 1
            

        yearNum = 2017
        return theCounty



if __name__ == "__main__":
    
    """
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
    """
    
    
    
    for county in COUNTIES:
        #dataFile = pd.read_csv(PA_25_PATHS[0])
        yearNum = 2017
        
        
        for i in range(1):
            dataFile = pd.read_csv(PA_25_PATHS[i])
            data2 = pd.read_csv(PA_10_PATHS[i])
            
            dataFile.drop(columns=DROP_COLS, inplace=True)
            data2.drop(columns=DROP_COLS, inplace=True)
            
            # delete unshared counties
            data2 = data2[data2["COUNTY"].isin(dataFile["COUNTY"])]
            dataFile = dataFile[dataFile["COUNTY"].isin(data2["COUNTY"])]

            #dont permanently mute this variable anymore

            theCounty = dataFile[dataFile.COUNTY == county]
            county2 = data2[data2.COUNTY == county]
            
            theCounty['Datetime'] =  pd.to_datetime(theCounty['Date'], format='%m/%d/%Y')
            county2["Datetime"] = pd.to_datetime(data2["Date"], format='%m/%d/%Y')
            theCounty.set_index('Datetime', inplace=True)
            county2.set_index('Datetime', inplace=True)

            theCounty = theCounty.resample('M').mean()
            county2 = county2.resample('M').mean()

            
            if (len(theCounty) > 2) and (len(county2) > 2):
                plt.figure(figsize=(10,5))
                plt.xticks(rotation=70)
                plt.plot(theCounty.index[::1], theCounty["Daily Mean PM2.5 Concentration"].iloc[::1])
                plt.plot(county2.index[::1], county2["Daily Mean PM10 Concentration"].iloc[::1])
                plt.legend(['PM 2.5', 'PM 10'])

                plt.title(str(yearNum) + " PM Concentration in " + county + ", MD")
                plt.xlabel("Date")
                plt.ylabel("Monthly Mean PM Concentration (ug/m3)")
                plt.show()
                yearNum += 1
            
             
        yearNum = 2017
        #theCounty = BaltCo()
        # baltco 2017 = 7.78
        # baltco 2021 = 8.03
        
        
        
        
      