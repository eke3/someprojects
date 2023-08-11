#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Jul 24 18:06:47 2022

@author: eric
"""

import matplotlib.dates as mdates
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import itertools

# Keep these columns
columns = ['AOD_340nm',
           'AOD_380nm',
           'AOD_440nm',
           'AOD_532nm',
           "AOD_675nm",
           'AOD_709nm',
           "AOD_870nm", 
           "AOD_1020nm", 
           "AOD_1640nm", 
           '380-500_Angstrom_Exponent',
           '440-675_Angstrom_Exponent',
           '500-870_Angstrom_Exponent',
           'Data_Quality_Level',
           'AERONET_Instrument_Number',
           'AERONET_Site_Name',
           'Site_Latitude(Degrees)',
           'Site_Longitude(Degrees)']

def AERONET_reduce(df):
    df = df.filter(columns)
    df.replace(-999, np.nan, inplace=True)
    return df

def AERONET_Datetime(df): 
    df["Datetime"] = pd.to_datetime([(f"{df.iloc[i, 0]}" + str(df.iloc[i, 1])) for i in range(len(df))], format="%d:%m:%Y%H:%M:%S")
    df.set_index(["Datetime"], inplace=True)
    return df

def AERONET_reduce(df):
    df = df.filter(columns)
    df.replace(-999, np.nan, inplace=True)
    return df

def AERONET_dict(df):
    AOD = df.filter(like='AOD_') # Get only columns starting with AOD
    AOD = AOD.resample("30T").mean() # Get only columns starting with AOD
    
    Ang = df.filter(like='_Angstrom_Exponent') # Get only columns ending with _Angstrom_Exponent
    Ang = Ang.resample("30T").mean() # Get only columns starting with AOD
    
    Info = df.filter(items = columns[-5::]).iloc[0]
    Info.head()
    
    return {"AOD": AOD, "Ang":Ang, "Info":Info}

def AERONET_plot_AODvsAOD(AOD1, AOD2, Info1, Info2):
    fig, (ax1, ax2) = plt.subplots(nrows=1, ncols=2, figsize=(20, 10))

    markers = itertools.cycle(('o', 'v', 's', 'd', '*')) 
    
    ### ------- Axis 1 ------- ### 
    for col in AOD1.columns:
        ax1.plot(AOD1.index, AOD1[col], label=f"{col}", linestyle='--', marker = next(markers))
    
    box = ax1.get_position()
    ax1.set_position([box.x0, box.y0, box.width * 0.8, box.height])

    # Put a legend to the right of the current axis
    ax1.legend(loc='center left', bbox_to_anchor=(1, 0.5))
    
    ax1.title.set_text(Info1.to_string())
    ax1.xaxis.set_major_formatter(mdates.DateFormatter('%m-%d %H'))
    ax1.set_xlabel("Datetime (UTC)")
    ax1.set_ylabel("AOD")
    ax1.grid(True)
    
    ### ------- Axis 2 ------- ### 
    for col in AOD2.columns:
        ax2.plot(AOD2.index, AOD2[col], label=f"{col}", linestyle='--', marker = next(markers))

    box = ax2.get_position()
    ax2.set_position([box.x0, box.y0, box.width * 0.8, box.height])

    # Put a legend to the right of the current axis
    ax2.legend(loc='center left', bbox_to_anchor=(1, 0.5))
    ax2.title.set_text(Info2.to_string())
    ax2.xaxis.set_major_formatter(mdates.DateFormatter('%m-%d %H'))
    ax2.set_xlabel("Datetime (UTC)")
    ax2.set_ylabel("AOD")
    ax2.grid(True)
    
    ### ------- Global ------- ###
    fig.tight_layout()
    # set the spacing between subplots
    plt.subplots_adjust(wspace=0.4)
    
    plt.savefig(r"AERONET_AOD_GSFC_UMBC_20210518_20210522.png", dpi=600, bbox_inches='tight')
    plt.show()
    return

def AERONET_plot_AODvsAOD_2(AOD1, AOD2, Info1, Info2):
    fig, (ax1, ax2) = plt.subplots(nrows=1, ncols=2, figsize=(20, 10))

    markers = itertools.cycle(('o', 'v', 's', 'd', '*')) 
    
    ### ------- Axis 1 ------- ### 
    for col in AOD1.columns:
        ax1.plot(AOD1.index, AOD1[col], label=f"{col}", linestyle='--', marker = next(markers))
    
    box = ax1.get_position()
    ax1.set_position([box.x0, box.y0, box.width * 0.8, box.height])

    # Put a legend to the right of the current axis
    ax1.legend(loc='center left', bbox_to_anchor=(1, 0.5))
    
    ax1.title.set_text(Info1.to_string())
    ax1.xaxis.set_major_formatter(mdates.DateFormatter('%m-%d %H'))
    ax1.set_xlabel("Datetime (UTC)")
    ax1.set_ylabel("AOD")
    ax1.grid(True)
    ax1.set_xlim([np.datetime64("2021-05-21 12:00"), np.datetime64("2021-05-22")])
    
    ### ------- Axis 2 ------- ### 
    for col in AOD2.columns:
        ax2.plot(AOD2.index, AOD2[col], label=f"{col}", linestyle='--', marker = next(markers))

    box = ax2.get_position()
    ax2.set_position([box.x0, box.y0, box.width * 0.8, box.height])

    # Put a legend to the right of the current axis
    ax2.legend(loc='center left', bbox_to_anchor=(1, 0.5))
    ax2.title.set_text(Info2.to_string())
    ax2.xaxis.set_major_formatter(mdates.DateFormatter('%m-%d %H'))
    ax2.set_xlabel("Datetime (UTC)")
    ax2.set_ylabel("AOD")
    ax2.grid(True)
    ax2.set_xlim([np.datetime64("2021-05-21 12:00"), np.datetime64("2021-05-22")])
    
    ### ------- Global ------- ###
    fig.tight_layout()
    # set the spacing between subplots
    plt.subplots_adjust(wspace=0.4)
    
    plt.savefig(r"AERONET_AOD_GSFC_UMBC_20210521.png", dpi=600, bbox_inches='tight')
    plt.show()
    return


if __name__ == "main":
    UMBC = pd.read_csv(r"/home/eric/Documents/SaSa/Reseach Project/Datasets/AERONET/UMBC/20220706_20220712_UMBC.lev15", sep=",", skiprows=6)
    GSFC = pd.read_csv(r"/home/eric/Documents/SaSa/Reseach Project/Datasets/AERONET/GSFC/20220706_20220712_GSFC.lev15", sep=",", skiprows=6)
    
    UMBC = AERONET_Datetime(UMBC)
    UMBC = UMBC["2022-07-06":"2022-07-12"]
    UMBC = AERONET_reduce(UMBC)
    UMBC = AERONET_dict(UMBC)
    
    AERONET_plot_AODvsAOD(GSFC["AOD"], UMBC["AOD"], GSFC["Info"], UMBC["Info"])
#UMBC

#AERONET_plot_AODvsAOD(Brookhaven["AOD"], UMBC["AOD"], Brookhaven["Info"], UMBC["Info"])