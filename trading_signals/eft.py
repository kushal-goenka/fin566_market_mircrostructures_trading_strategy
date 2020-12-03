# -*- coding: utf-8 -*-
"""
@file: eft
@author: Yong Xie
@time: 12/2/2020 11:43 PM
@Description: 

This script is used to contain utility function involved with eft.

"""

from os.path import join as join
import pandas as pd
import numpy as np
import datetime
from collections import defaultdict

col_names = ['COLLECTION_TIME', 'SOURCE_TIME', 'SEQ_NUM', 'TICK_TYPE', 'MARKET_CENTER', 'PRICE', 'SIZE']

def calc_theoretical_eft_price(input, output, dates, tickers, weights):
    """

    # This function integrate trade orders from each eft component to generate
    # theoretical price process for the eft.

    # Aggregation by COLLECTION_TIME. 

    # Data input follows the exact same format as sample data in 
    # https://davidl.web.engr.illinois.edu/data/20191030_marketdata/ticks_201910.tar.bz2

    # data file in the format: tick_{ticker}_{yyyymmdd}.txt

    Args:
        input (str): folder of order data
        output (str): output folder
        dates ([str]): [date]
        tickers ([str]): tickers for components]
        weights ([numeric]): list of component weights corresponding to tickers
    
    Returns:
        Price process for each order update
    """

    for date in dates:

        # read data
        comps_data = pd.DataFrame()
        for ticker in tickers:
            ticker_data = pd.read_csv(join(input, 'tick_{}_{}.txt'.format(ticker, date)), 
                                    names=col_names, parse_dates=[0, 1])
            ticker_data['TIKCER'] = ticker
            comps_data = pd.concat([comps_data, ticker_data], axis=0)
        
        comps_data = comps_data.sort_values('COLLECTION_TIME')
        comps_data_matrix = comps_data.values

        # aggregate price
        ticker_prices, curr_price = {}, None
        eft_price = []
        
        for i in range(comps_data.shape[0]):
            
            ticker = comps_data_matrix[i, 7]
            curr_ticker_price = comps_data_matrix[i, 5]

            if curr_price:
                curr_price += (- ticker_prices[ticker] + curr_ticker_price)
                curr_price = round(curr_price, 2)
                ticker_prices[ticker] = curr_ticker_price
            else:
                ticker_prices[ticker] = curr_ticker_price
                if len(ticker_prices) == len(tickers):
                    curr_price = sum(ticker_prices.values())

            eft_price.append(curr_price)

        comps_data['ETF_PRICE'] = eft_price
        comps_data.to_csv(join(output, 'tick_DIAEFT_{}.txt'.format(date)), index=False)

        print('finished {}'.format(date))

