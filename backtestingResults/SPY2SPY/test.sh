cd /home/vagrant/Desktop/strategy_studio/backtesting/backtesting-cra-exports
latestPnL=$(ls -t grep *pnl* | head -1)
tail -1 $latestPnL
cd /home/vagrant/Desktop/strategy_studio/backtesting/utilities
