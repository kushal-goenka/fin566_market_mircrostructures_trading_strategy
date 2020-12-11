/*================================================================================                               
*     Source: ../RCM/StrategyStudio/examples/strategies/SimpleMomentumStrategy/SimpleMomentumStrategy.cpp                                                        
*     Last Update: 2013/6/1 13:55:14                                                                            
*     Contents:                                     
*     Distribution:          
*                                                                                                                
*                                                                                                                
*     Copyright (c) RCM-X, 2011 - 2013.                                                  
*     All rights reserved.                                                                                       
*                                                                                                                
*     This software is part of Licensed material, which is the property of RCM-X ("Company"), 
*     and constitutes Confidential Information of the Company.                                                  
*     Unauthorized use, modification, duplication or distribution is strictly prohibited by Federal law.         
*     No title to or ownership of this software is hereby transferred.                                          
*                                                                                                                
*     The software is provided "as is", and in no event shall the Company or any of its affiliates or successors be liable for any 
*     damages, including any lost profits or other incidental or consequential damages relating to the use of this software.       
*     The Company makes no representations or warranties, express or implied, with regards to this software.                        
/*================================================================================*/   

#ifdef _WIN32
    #include "stdafx.h"
#endif

#include "Team3Strategy.h"

#include "FillInfo.h"
#include "AllEventMsg.h"
#include "ExecutionTypes.h"
#include <Utilities/Cast.h>
#include <Utilities/utils.h>

#include <math.h>
#include <iostream>
#include <cassert>

using namespace RCM::StrategyStudio;
using namespace RCM::StrategyStudio::MarketModels;
using namespace RCM::StrategyStudio::Utilities;

using namespace std;

SimpleTrade::SimpleTrade(StrategyID strategyID, const std::string& strategyName, const std::string& groupName):
    Strategy(strategyID, strategyName, groupName),
    m_momentum_map(),
    m_instrument_order_id_map(),
    m_momentum(0),
    m_aggressiveness(0),
    m_position_size(100),
    m_debug_on(true),
    m_short_window_size(10),
    m_long_window_size(30)
{
    //this->set_enabled_pre_open_data_flag(true);
    //this->set_enabled_pre_open_trade_flag(true);
    //this->set_enabled_post_close_data_flag(true);
    //this->set_enabled_post_close_trade_flag(true);
}

// SimpleTrade::~SimpleTrade()
// {
// }

void SimpleTrade::OnResetStrategyState()
{




}

void SimpleTrade::DefineStrategyParams()
{




}

void SimpleTrade::DefineStrategyCommands()
{




}

void SimpleTrade::RegisterForStrategyEvents(StrategyEventRegister* eventRegister, DateType currDate)
{    

}
void SimpleTrade::OnTrade(const TradeDataEventMsg& msg)
{
	

}
void SimpleTrade::OnBar(const BarEventMsg& msg)
{
    



}

void SimpleTrade::OnOrderUpdate(const OrderUpdateEventMsg& msg)
{    
	
}

void SimpleTrade::AdjustPortfolio(const Instrument* instrument, int desired_position)
{
   
}

void SimpleTrade::SendSimpleOrder(const Instrument* instrument, int trade_size)
{

	
}


void SimpleTrade::SendOrder(const Instrument* instrument, int trade_size)
{
	
}

void SimpleTrade::RepriceAll()
{

}

void SimpleTrade::Reprice(Order* order)
{
    


}

void SimpleTrade::OnStrategyCommand(const StrategyCommandEventMsg& msg)
{
   
}

void SimpleTrade::OnParamChanged(StrategyParam& param)
{    
	
}
