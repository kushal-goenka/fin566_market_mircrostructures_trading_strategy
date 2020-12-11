instanceName="S4"
strategyName="SimpleTrade"
startDate="2019-10-29"
endDate="2019-10-30"
sharedObjectFileName="SimpleTradeStrategy.so"
sharedObjectOriginPath="/home/vagrant/Desktop/strategy_studio/localdev/RCM/StrategyStudio/examples/strategies/SimpleTradeStrategy/$sharedObjectFileName"
sharedObjectDestinationPath="/home/vagrant/Desktop/strategy_studio/backtesting/strategies_dlls"

# cp $sharedObjectOriginPath $sharedObjectDestinationPath
# /home/vagrant/Desktop/strategy_studio/backtesting/./StrategyServerBacktesting&

# (cd /home/vagrant/Desktop/strategy_studio/backtesting && ./StrategyServerBacktesting&)

/home/vagrant/Desktop/strategy_studio/backtesting/utilities/./StrategyCommandLine cmd create_instance $instanceName $strategyName UIUC SIM-1001-101 dlariviere 1000000 -symbols SPY

logFileNumLines=$(wc -l < /home/vagrant/Desktop/strategy_studio/backtesting/logs/main_log.txt)
echo "Number of lines Currently in Log file:",$logFileNumLines

/home/vagrant/Desktop/strategy_studio/backtesting/utilities/./StrategyCommandLine cmd start_backtest $startDate $endDate $instanceName 1

foundFinishedLogFile=$(grep -nr "finished.$" /home/vagrant/Desktop/strategy_studio/backtesting/logs/main_log.txt | gawk '{print $1}' FS=":"|tail -1)
echo "Last line found:",$foundFinishedLogFile

while ((logFileNumLines > foundFinishedLogFile))
do

foundFinishedLogFile=$(grep -nr "finished.$" /home/vagrant/Desktop/strategy_studio/backtesting/logs/main_log.txt | gawk '{print $1}' FS=":"|tail -1)

done

echo "Last line found after ending:",$foundFinishedLogFile

# /home/vagrant/Desktop/strategy_studio/backtesting/utilities/./StrategyCommandLine cmd start_backtest 2019-10-30 2019-10-30 $instanceName 1
latestCRA=$(ls -t /home/vagrant/Desktop/strategy_studio/backtesting/backtesting-results | head -1)
echo "latest CRA File is: $latestCRA"
/home/vagrant/Desktop/strategy_studio/backtesting/utilities/./StrategyCommandLine cmd export_cra_file backtesting-results/$latestCRA backtesting-cra-exports

# /home/vagrant/Desktop/strategy_studio/backtesting/utilities/./StrategyCommandLine cmd quit

# logFileNumLines=$(wc -l < /home/vagrant/Desktop/strategy_studio/backtesting/logs/main_log.txt)
# echo "Number of lines:",$logFileNumLines