# -*- coding: utf-8 -*-
#Coded using colab.research.google.com

# IMPORTING DATA FROM GOOGLE DRIVE
from google.colab import drive 
drive.mount('/content/gdrive')

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

# READING THE FILES
wholedf = pd.read_csv('gdrive/My Drive/dowjones_ticks.csv')
print(wholedf.shape)

dia = pd.read_csv('gdrive/My Drive/dia.csv')
print(dia.shape)

# Time series plot with price

fig, axs = plt.subplots(4, 4, figsize=(20,12))
axs[0, 0].plot(wholedf[wholedf['ticker']=='AAPL'].price)
axs[0, 0].set_title('AAPL')
axs[0, 1].plot(wholedf[wholedf['ticker']=='AXP'].price)
axs[0, 1].set_title('AXP')
axs[0, 2].plot(wholedf[wholedf['ticker']=='BA'].price)
axs[0, 2].set_title('BA')
axs[0, 3].plot(wholedf[wholedf['ticker']=='CAT'].price)
axs[0, 3].set_title('CAT')
axs[1, 0].plot(wholedf[wholedf['ticker']=='CSCO'].price)
axs[1, 0].set_title('CSCO')
axs[1, 1].plot(wholedf[wholedf['ticker']=='CVX'].price)
axs[1, 1].set_title('CVX')
axs[1, 2].plot(wholedf[wholedf['ticker']=='DIS'].price)
axs[1, 2].set_title('DIS')
axs[1, 3].plot(wholedf[wholedf['ticker']=='DOW'].price)
axs[1, 3].set_title('DOW')
axs[2, 0].plot(wholedf[wholedf['ticker']=='GS'].price)
axs[2, 0].set_title('GS')
axs[2, 1].plot(wholedf[wholedf['ticker']=='HD'].price)
axs[2, 1].set_title('HD')
axs[2, 2].plot(wholedf[wholedf['ticker']=='IBM'].price)
axs[2, 2].set_title('IBM')
axs[2, 3].plot(wholedf[wholedf['ticker']=='INTC'].price)
axs[2, 3].set_title('INTC')
axs[3, 0].plot(wholedf[wholedf['ticker']=='JNJ'].price)
axs[3, 0].set_title('JNJ')
axs[3, 1].plot(wholedf[wholedf['ticker']=='JPM'].price)
axs[3, 1].set_title('JPM')
axs[3, 2].plot(wholedf[wholedf['ticker']=='KO'].price)
axs[3, 2].set_title('KO')
axs[3, 3].plot(wholedf[wholedf['ticker']=='MCD'].price)
axs[3, 3].set_title('MCD')
plt.subplots_adjust(wspace=0.35, hspace=0.35)
plt.show()


fig, axs = plt.subplots(4, 4, figsize=(20,12))
axs[0, 0].plot(wholedf[wholedf['ticker']=='MMM'].price)
axs[0, 0].set_title('MMM')
axs[0, 1].plot(wholedf[wholedf['ticker']=='MRK'].price)
axs[0, 1].set_title('MRK')
axs[0, 2].plot(wholedf[wholedf['ticker']=='MSFT'].price)
axs[0, 2].set_title('MSFT')
axs[0, 3].plot(wholedf[wholedf['ticker']=='NKE'].price)
axs[0, 3].set_title('NKE')
axs[1, 0].plot(wholedf[wholedf['ticker']=='PFE'].price)
axs[1, 0].set_title('PFE')
axs[1, 1].plot(wholedf[wholedf['ticker']=='PG'].price)
axs[1, 1].set_title('PG')
axs[1, 2].plot(wholedf[wholedf['ticker']=='TRV'].price)
axs[1, 2].set_title('TRV')
axs[1, 3].plot(wholedf[wholedf['ticker']=='UNH'].price)
axs[1, 3].set_title('UNH')
axs[2, 0].plot(wholedf[wholedf['ticker']=='UTX'].price)
axs[2, 0].set_title('UTX')
axs[2, 1].plot(wholedf[wholedf['ticker']=='V'].price)
axs[2, 1].set_title('V')
axs[2, 2].plot(wholedf[wholedf['ticker']=='VZ'].price)
axs[2, 2].set_title('VZ')
axs[2, 3].plot(wholedf[wholedf['ticker']=='WBA'].price)
axs[2, 3].set_title('WBA')
axs[3, 0].plot(wholedf[wholedf['ticker']=='WMT'].price)
axs[3, 0].set_title('WMT')
axs[3, 1].plot(wholedf[wholedf['ticker']=='XOM'].price)
axs[3, 1].set_title('XOM')
fig.delaxes(axs[3,2])
fig.delaxes(axs[3,3])
plt.subplots_adjust(wspace=0.35, hspace=0.35)
plt.show()

#data = wholedf.groupby(['ticker'])
#print(data)

#d1=pd.read_csv('gdrive/My Drive/FIN566/tick_DIAEFT_20191031.txt')
#d1.tail(20)