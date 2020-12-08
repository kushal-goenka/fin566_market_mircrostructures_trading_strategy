# -*- coding: utf-8 -*-
"""
@file: correlation.py
@author: Yong Xie
@time: 12/7/2020 12:01 PM
@Description: 

This cript is used to generate pairwise correlation between component and eft

"""

import pandas as pd
import matplotlib.pyplot as plt
import os

col_names = ['COLLECTION_TIME', 'SOURCE_TIME', 'SEQ_NUM', 'TICK_TYPE', 'MARKET_CENTER', 'PRICE', 'SIZE']

def comp_corr(input_folder, output_folder, dates, etf_ticker, comp_ticker):
    """

    # Calculate correlation between components and eft price

    Args:
        input_folder (str): tick data folder
        output_folder ([type]): output folder
        dates (list of str): yyyymmdd
        etf_ticker (str): ticker for etf of interest
        comp_ticker (list of ticker): component tickers
    Returns:
        csv file with each row represent correlation of corresponding ticker with eft
        and each column represent the date.

    """

    correlations = {}
    for date in dates:

        date_corr = {}

        etf = pd.read_csv(os.path.join(input_folder, 'tick_{}_{}.txt'.format(etf_ticker, date)), 
                                    names=col_names, parse_dates=[0, 1])

        for ticker in tickers:
            comp = pd.read_csv(os.path.join(input_folder, 'tick_{}_{}.txt'.format(ticker, date)), 
                                        names=col_names, parse_dates=[0, 1])

            combine = pd.merge(left=etf, right=comp, left_on='COLLECTION_TIME', right_on='COLLECTION_TIME', how='outer')
            combine = combine.sort_values('COLLECTION_TIME')

            combine = combine.fillna(method='pad', axis=0)
            corr = combine[['PRICE_x', 'PRICE_y']].corr()
            date_corr[ticker] = corr.iloc[1,0]
        correlations[date] = date_corr

        print('finished {}'.format(date))

    pd.DataFrame(correlations).to_csv(os.path.join(output_folder, 'correlation_{}.csv'.format(etf_ticker)))


if __name__ == '__main__':
    
    tickers = [
        'XOM', 'KO', 'IBM', 'PG', 'UTX', 'MMM', 'MRK', 'AXP', 'MCD', 'CAT', 
        'DIS', 'JNJ', 'WMT', 'HD', 'INTC', 'MSFT', 'JPM', 'VZ', 'PFE', 
        'CVX', 'CSCO', 'TRV', 'UNH', 'NKE', 'GS', 'V', 'AAPL', 'WBA', 'DOW'
        ]

    weights = [1] * len(tickers)

    input_folder = r'G:\FIN566\ticks_201910'
    output_folder = r'G:\FIN566\ticks_201910'
    dates = [
        '20191001', '20191002', '20191003', '20191004',
        '20191007', '20191008', '20191009', '20191010',
        '20191011', '20191014', '20191015', '20191016',
        '20191017', '20191018', '20191021', '20191022',
        '20191023', '20191024', '20191025', '20191028',
        '20191029', '20191030', '20191031', '20191101'   
        ]
    comp_corr(input_folder, output_folder, dates, 'DIA', tickers)