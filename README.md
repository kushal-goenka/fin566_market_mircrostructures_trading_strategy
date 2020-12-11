
# FIN 566 Fall 2020 Team 3 Final Project


 Implementation of a High Frequency trading Strategy using the Strategy Studio backtesting software

## Group info:
___

Khavya Chandrasekaran khavyac2@illinois.edu - MSFE

Xuehui Chao xuehuic2@illinois.edu - MSFE

Yong Xie yongxie2@illinois.edu - PhD Mathematics

Kushal Goenka kgoenka2@illinois.edu - MEng Electrical and Computer Engineering

---

## Project Structure

- **strategy_studio**: contains strategy implementation in strategy studio
- **trading_signals**: trading signal analysis code for the strategy, mostly in Python.
- **metrics**: portfolio and strategy evaluation metric module.

## Weekly Zoom Link Meeting:
___

Join Zoom Meeting
https://illinois.zoom.us/j/89410527998?pwd=ZzJQbGpCb1NxY3N2dkk2Y1JCTkhxQT09

Meeting ID: 894 1052 7998
Password: 172526

## How to run a Strategy
___

- First Build the required strategy via:

        cd /home/vagrant/Desktop/fin566_fall_2020_group_three/strategy_studio/localdev/RCM/StrategyStudio/examples/strategies/Team3Strategy

        make clean

        make all

- This results in a <"StrategyName">.so file.

        /home/vagrant/Desktop/strategy_studio/backtesting/./StrategyServerBacktesting

- Copy it over to the required folder
        cp /home/vagrant/Desktop/strategy_studio/RCM/StrategyStudio/examples/strategies/Team3Strategy/Team3Strategy.so /home/vagrant/Desktop/strategy_studio/backtesting/strategies_dlls

- Create an instance of the trading strategy

        create_instance Team3StrategyForSPY Team3Strategy UIUC SIM-1001-101 dlariviere 10000000 -symbols SPY

- Start the backtest
        
        start_backtest 2019-10-30 2019-10-30 Team3StrategyForSPY 1

- Now, find the local name of the most recently run backtest, by running
        
        ls -lA /home/vagrant/Desktop/strategy_studio/backtesting/backtesting-results
- To export the files and convert to CSV files:

        export_cra_file backtesting-results/BACK_SimpleTradePairsTest_2019-11-19_045116_start_10-30-2019_end_10-30-2019.cra backtesting-cra-exports

- The results will be in:

        cd /home/vagrant/Desktop/strategy_studio/backtesting/backtesting-cra-exports



## Important Links:

https://davidl.web.engr.illinois.edu/data/20191030_marketdata/

https://davidl.web.engr.illinois.edu/fin566_fall_2020/lecture_videos/index.html

RCM Strategy Studio API Documentation: https://davidl.web.engr.illinois.edu/data/20191030_marketdata/rcm/RCM/StrategyStudio/docs/html/


RCM's Strategy Studio CSV input data format (if your project outputs in this format, you will later have an easier time backtesting on that data using strategy studio): https://davidl.web.engr.illinois.edu/data/20191030_marketdata/TextTickReader.pdf


Additional Strategy-Studio formatted ticks (trades) data decoded from IEX for most of month of October (2019-10-01 through 2019-10-30): link; Extract into the backtesting/text_tick_data folder using "tar -xjf ticks_201910.tar.bz2". This includes data for SPY,IVV,VOO,VXX,QQQ,TLT,LQD,HYG,USO,SPXL,DDG,FINZ,OILD,PSQ,PST,SDS,MSFT,AAPL,AMZN,FB,GOOGL,GOOG,DIA,BA,UNH,AAPL,GS,HD,MCD,V,MMM,UTX,DIS,CAT,JNJ,TRV,JPM,IBM,PG,AXP,WMT,CVX,NKE,MRK,XOM,VZ,WBA,INTC,KO,DOW,CSCO,PFE

https://davidl.web.engr.illinois.edu/data/20191030_marketdata/ticks_201910.tar.bz2

