#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 25 15:37:34 2022

@author: eric
"""
import pandas as pd
import datetime
import matplotlib.pyplot as plt


keepcols = ["Abs470_total", "Abs532_total", "Abs660_total", "AEabsDRY_470to660nm", "Time_Mid"]


path = [r"/home/eric/Documents/SaSa/Reseach Project/Datasets/LARGE/SASA-LARGE-OPTICAL_P3B_20220712_RA_L1.ict", r"/home/eric/Documents/SaSa/Reseach Project/Datasets/LARGE/SASA-LARGE-MICROPHYSICAL_P3B_20220712_RA_L1.ict"]

if __name__ == "__main__":
    
    dataOptical = pd.read_csv(path[0], sep=',', skiprows=86)
    allcols = list(dataOptical.columns)
    for col in keepcols:
        if col in allcols:
            allcols.remove(col)
    dataOptical.drop(columns=allcols, inplace=True)
    dataOptical['Datetimes'] =  pd.to_datetime(dataOptical['Time_Mid'], unit='s', origin='2022-07-12')
    dataOptical.set_index('Datetimes', inplace=True) 
    
    
    dataOptical = dataOptical[dataOptical.AEabsDRY_470to660nm != -9999]
    

    plt.figure(figsize=(10,8))
    plt.xlabel("Time")
    plt.ylabel("AE 470to660nm")
    plt.title("2022-07-12 Angstrom Exponent")
    plt.xticks(rotation=70)
    plt.plot(dataOptical.index[::1], dataOptical['AEabsDRY_470to660nm'].iloc[::1], 'r--')
    plt.show()
    
    top = dataOptical[dataOptical.AEabsDRY_470to660nm >1]
    bottom =dataOptical[(dataOptical.AEabsDRY_470to660nm < 1)]
    bottom = bottom[bottom.AEabsDRY_470to660nm != -9999]