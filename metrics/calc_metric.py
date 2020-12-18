# -*- coding: utf-8 -*-
"""
@file: correlation.py
@author: Yong Xie
@time: 12/17/2020 12:01 PM
@Description: 

This cript is used to generate portfolio metric automately.

The main function of this script come from Alice.

"""

import pandas as pd
import os
import numpy as np
import pandas as pd
import collections
import scipy.stats as st
import seaborn as sns
import collections
import matplotlib.pyplot as plt

# DISPLAY ALL THE COLUMNS IN CASE 
pd.set_option('display.max_columns', None)

#SET THE PATH TO LOCAL
os.chdir('/home/vagrant/Desktop/strategy_studio/backtesting/')

# read data
path = '/home/vagrant/Desktop/strategy_studio/backtesting/backtesting-cra-exports'
files = os.listdir(path)
paths = [os.path.join(path, basename) for basename in files]
latest = sorted(paths, key=os.path.getctime)[-3:]

order = pd.read_csv(latest[0])
pnl = pd.read_csv(latest[1])
fill = pd.read_csv(latest[2])


# caluclate cummulative return
total_invest=[]
total_cost=[]
for i in range(len(pnl)):
    total_invest.append(sum(fill[fill['TradeTime']<=pnl['Time'].loc[i]].Price))
    total_cost.append(sum(fill[fill['TradeTime']<=pnl['Time'].loc[i]].ExecutionCost))
pnl['total_invest']=total_invest
pnl['total_cost']=total_cost
pnl['cumu_return_percentage']=pnl['Cumulative PnL']/pnl['total_invest']

pnl['simplereturn']=0
for i in range(len(pnl)):
    if i==0:
        pnl['simplereturn'].loc[i]=pnl['cumu_return_percentage'].loc[i]
    else:
        pnl['simplereturn'].loc[i]=(1+pnl['cumu_return_percentage'].loc[i])/(1+pnl['cumu_return_percentage'].loc[i-1])-1

plt.figure(figsize=(18,10))
plt.ylabel('Cumulative Return ',fontsize="xx-large")
plt.title('Cumulative Return ',fontsize="xx-large")
plt.gca().yaxis.grid(True)
plt.plot(pnl['cumu_return_percentage'],color='red',label="Q1",lw=3)


# calculate sharpe ratio and others

year=1/252

cumure=pnl[-1:]
cr=cumure[[ 'cumu_return_percentage']]#'Cumulative_return_CompQ5-Q1']]#'Cumulative_return_CompSP500']]
cr['Annualized']=(cr['cumu_return_percentage']+1)**(1/year)-1#this is only calculated using 1 days return, has large bias
cr['vol']=np.sqrt(pnl['simplereturn'].var()*252*330)#yearly

cr['Sharpe']=cr['Annualized']/cr['vol']
pnl['downside_returns'] = 0

rfr = 0
target = 0
pnl.loc[pnl['simplereturn'] < target, 'downside_returns'] = pnl['simplereturn']**2

down_stdev = np.sqrt(pnl['downside_returns'].mean()*330*252)
cr['Sortino']=cr['Annualized']/down_stdev

cr['T-Stat']=st.ttest_1samp(pnl['simplereturn'],0).statistic
cr['P-Value']= st.ttest_1samp(pnl['simplereturn'],0).pvalue

cr.to_csv(os.path.join(path, latest[0][:-9]+'metric.csv'))

print(cr)