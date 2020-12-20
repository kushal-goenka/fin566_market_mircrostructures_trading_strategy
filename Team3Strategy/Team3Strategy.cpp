#ifdef _WIN32
    #include "stdafx.h"
#endif

#include "Team3Strategy.h"

#include "FillInfo.h"
#include "AllEventMsg.h"
#include "ExecutionTypes.h"
#include <Utilities/Cast.h>
#include <Utilities/utils.h>
#include "DataTypes.h"

#include <math.h>
#include <iostream>
#include <cassert>

using namespace RCM::StrategyStudio;
using namespace RCM::StrategyStudio::MarketModels;
using namespace RCM::StrategyStudio::Utilities;

using namespace std;

Team3Strategy::Team3Strategy(StrategyID strategyID, const std::string& strategyName, const std::string& groupName):
    Strategy(strategyID, strategyName, groupName),
    m_momentum_map(),
    m_instrument_order_id_map(),
    m_momentum(0),
    m_aggressiveness(0.00),
    m_position_size(100),
    m_debug_on(true),
    m_short_window_size(10),
    m_long_window_size(30),

    instrucmentSignal(NULL),
    instrucmentTrade(NULL),
    signal("SPY"),
    totrade("COMP"),

    signalLastPrice {0, 0},
    tradeLastPrice {0, 0},
    currentState(START),
    quantityHeld(0), 
    lastExePrice(0),

    upThreshold(0.05),               // parameter to tune
    downThreshold(0.05)              // parameter to tune

{
    //cout << "GROUP NAME" << groupName << endl;
    //this->set_enabled_pre_open_data_flag(true);
    //this->set_enabled_pre_open_trade_flag(true);
    //this->set_enabled_post_close_data_flag(true);
    //this->set_enabled_post_close_trade_flag(true);
}

Team3Strategy::~Team3Strategy()
{
}

void Team3Strategy::OnResetStrategyState()
{
    // m_momentum_map.clear();
    // m_instrument_order_id_map.clear();
    // m_momentum = 0;
}

void Team3Strategy::DefineStrategyParams()
{
    // CreateStrategyParamArgs arg1("aggressiveness", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_DOUBLE, m_aggressiveness);
    // params().CreateParam(arg1);

    // CreateStrategyParamArgs arg2("position_size", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_INT, m_position_size);
    // params().CreateParam(arg2);

    // CreateStrategyParamArgs arg3("short_window_size", STRATEGY_PARAM_TYPE_STARTUP, VALUE_TYPE_INT, m_short_window_size);
    // params().CreateParam(arg3);
    
    // CreateStrategyParamArgs arg4("long_window_size", STRATEGY_PARAM_TYPE_STARTUP, VALUE_TYPE_INT, m_long_window_size);
    // params().CreateParam(arg4);
    
    // CreateStrategyParamArgs arg5("debug", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_BOOL, m_debug_on);
    // params().CreateParam(arg5);
}

void Team3Strategy::DefineStrategyCommands()
{
    // StrategyCommand command1(1, "Reprice Existing Orders");
    // commands().AddCommand(command1);

    // StrategyCommand command2(2, "Cancel All Orders");
    // commands().AddCommand(command2);
}

void Team3Strategy::RegisterForStrategyEvents(StrategyEventRegister* eventRegister, DateType currDate)
{    
    // for (SymbolSetConstIter it = symbols_begin(); it != symbols_end(); ++it) {
    //     eventRegister->RegisterForBars(*it, BAR_TYPE_TIME, 10);
    // }
}
void Team3Strategy::OnTrade(const TradeDataEventMsg& msg)
{   
    bool toBuy = false;
    bool toSell = false;
    
    // update signal - from signal ticker
    if((signal=="SPY" && msg.instrument().symbol()=="SPY") || (signal=="COMP" && msg.instrument().symbol()!="SPY")){

        // Receive new message from SPY: 

        // 1. Apply trade logic
        if(instrucmentSignal!=NULL){
            
            if(currentState==START){
                if(msg.trade().price() - min(signalLastPrice[1], signalLastPrice[2]) > upThreshold){
                    currentState = BUY;
                }   
            }

            if (currentState == HOLD){
                if(msg.trade().price() - max(signalLastPrice[1], signalLastPrice[2]) < - downThreshold){
                    currentState = SELL;
                }
            }
        }       

        // 2. Update historical info
        instrucmentSignal = &msg.instrument();
        signalLastPrice[1] = signalLastPrice[2];
        signalLastPrice[2] = msg.trade().price();
    }

    // update signal - from trade ticker
    if ((totrade=="SPY" && msg.instrument().symbol()=="SPY") || (totrade=="COMP" && msg.instrument().symbol()!="SPY")){
        
        // stop-loss and take-profit logic
        if(instrucmentSignal!=NULL){
            if(currentState == HOLD){
                if(msg.trade().price()/lastExePrice < 0.995 || msg.trade().price()/lastExePrice > 1.01){
                    currentState = SELL;
                }
            }
        }    
        instrucmentTrade = &msg.instrument();
        tradeLastPrice[1] = tradeLastPrice[2];
        tradeLastPrice[2] = msg.trade().price();
        tradeLastQuantity = msg.trade().size();
    }
    

    // Execute trade decision
    for (int i=0; i<1; i++){
        if(currentState == BUY){
            currentState = SENT_BUY;
            this->SendSimpleOrder(instrucmentTrade, tradeLastQuantity); //buy multiple shares, the component ticker
        }

        if(currentState == SELL){
            currentState = SENT_SELL;
            this->SendSimpleOrder(instrucmentTrade, -1 * quantityHeld);
        }
    }
}

void Team3Strategy::OnBar(const BarEventMsg& msg)
{
    // if (m_debug_on) {
    //     ostringstream str;
    //     str << "FINDME" << msg.instrument().symbol() << ": " << msg.bar();
    //     logger().LogToClient(LOGLEVEL_DEBUG, str.str().c_str());
    //     //std::cout << str.str().c_str() << std::endl;
    // }

    // if(msg.bar().close() < .01) return;


    // //check if we're already tracking the momentum object for this instrument, if not create a new one
    // MomentumMapIterator iter = m_momentum_map.find(&msg.instrument());
    // if (iter != m_momentum_map.end()) {
    //     m_momentum = &iter->second;
    // } else {
    //     m_momentum = &m_momentum_map.insert(make_pair(&msg.instrument(),Momentum(m_short_window_size,m_long_window_size))).first->second;
    // }

    // DesiredPositionSide side = m_momentum->Update(msg.bar().close());

    // if(m_momentum->FullyInitialized()) {
    //     AdjustPortfolio(&msg.instrument(), m_position_size * side);
    // }
}

void Team3Strategy::OnOrderUpdate(const OrderUpdateEventMsg& msg)
{    
    if(msg.completes_order())
    {
		m_instrument_order_id_map[msg.order().instrument()] = 0;

        if (currentState == SENT_BUY){
            currentState = HOLD;
            quantityHeld += abs(msg.order().size_completed());
            std::cout << "Update: buy order is complete; size: " << msg.order().size_completed() <<std::endl;

            if (abs(msg.order().size_completed()) > 0){
                lastExePrice = msg.order().price();
            }
        }   

        if (currentState == SENT_SELL){
            quantityHeld -= abs(msg.order().size_completed());
            std::cout << "Update: sell order is complete; size: " << msg.order().size_completed() <<std::endl;
                currentState = START;
        }   
    }
}

// void Team3Strategy::AdjustPortfolio(const Instrument* instrument, int desired_position)
// {
//     int trade_size = desired_position - portfolio().position(instrument);

//     if (trade_size != 0) {
//         OrderID order_id = m_instrument_order_id_map[instrument];
//         //if we're not working an order for the instrument already, place a new order
//         if (order_id == 0) {
//             SendOrder(instrument, trade_size);
//         } else {  
// 		    //otherwise find the order and cancel it if we're now trying to trade in the other direction
//             const Order* order = orders().find_working(order_id);
//             if(order && ((IsBuySide(order->order_side()) && trade_size < 0) || 
// 			            ((IsSellSide(order->order_side()) && trade_size > 0)))) {
//                 trade_actions()->SendCancelOrder(order_id);
//                 //we're avoiding sending out a new order for the other side immediately to simplify the logic to the case where we're only tracking one order per instrument at any given time
//             }
//         }
//     }
// }

void Team3Strategy::SendSimpleOrder(const Instrument* instrument, int trade_size)
{

	//this is simple check to avoid placing orders before the order book is actually fully initialized
	//side note: if trading certain futures contracts for example, the price of an instrument actually can be zero or even negative. here we assume cash US equities so price > 0
    /*
	if(instrument->top_quote().ask()<.01 || instrument->top_quote().bid()<.01 || !instrument->top_quote().ask_side().IsValid() || !instrument->top_quote().ask_side().IsValid()) {
        std::stringstream ss;
        ss << "SendSimpleOrder(): Sending buy order for " << instrument->symbol() << " at price " << instrument->top_quote().ask() << " and quantity " << trade_size <<" with missing quote data";
        logger().LogToClient(LOGLEVEL_DEBUG, ss.str());
        std::cout << "SendSimpleOrder(): " << ss.str() << std::endl;
        return;
     }*/

    double last_trade_price = instrument->last_trade().price();
    double price = trade_size > 0 ? last_trade_price + m_aggressiveness : last_trade_price - m_aggressiveness;

    OrderParams params(*instrument,
        abs(trade_size),
        price,
        (instrument->type() == INSTRUMENT_TYPE_EQUITY) ? MARKET_CENTER_ID_IEX : ((instrument->type() == INSTRUMENT_TYPE_OPTION) ? MARKET_CENTER_ID_CBOE_OPTIONS : MARKET_CENTER_ID_CME_GLOBEX),
        (trade_size>0) ? ORDER_SIDE_BUY : ORDER_SIDE_SELL,
        ORDER_TIF_DAY,
        ORDER_TYPE_LIMIT);

    cout << "Send order. size: " << trade_size << "; price: " << price << "; last trade price: " << last_trade_price << endl;
    TradeActionResult tra = trade_actions()->SendNewOrder(params);
    if (tra == TRADE_ACTION_RESULT_SUCCESSFUL) {
        m_instrument_order_id_map[instrument] = params.order_id;
    }
    else
    {
    	std::cout << "SendOrder(): Error sending new order!!!" << tra << std::endl;
    }

}


// void Team3Strategy::SendOrder(const Instrument* instrument, int trade_size)
// {
// 	return;
//     if(instrument->top_quote().ask()<.01 || instrument->top_quote().bid()<.01 || !instrument->top_quote().ask_side().IsValid() || !instrument->top_quote().ask_side().IsValid()) {
//         std::stringstream ss;
//         ss << "Sending buy order for " << instrument->symbol() << " at price " << instrument->top_quote().ask() << " and quantity " << trade_size <<" with missing quote data";   
//         logger().LogToClient(LOGLEVEL_DEBUG, ss.str());
//         std::cout << "SendOrder(): " << ss.str() << std::endl;
//         std::cout << "WORKING Call this function" << std::endl;
//         return;
//      }

//     double price = trade_size > 0 ? instrument->top_quote().bid() + m_aggressiveness : instrument->top_quote().ask() - m_aggressiveness;

//     OrderParams params(*instrument, 
//         abs(trade_size),
//         price, 
//         (instrument->type() == INSTRUMENT_TYPE_EQUITY) ? MARKET_CENTER_ID_NASDAQ : ((instrument->type() == INSTRUMENT_TYPE_OPTION) ? MARKET_CENTER_ID_CBOE_OPTIONS : MARKET_CENTER_ID_CME_GLOBEX),
//         (trade_size>0) ? ORDER_SIDE_BUY : ORDER_SIDE_SELL,
//         ORDER_TIF_DAY,
//         ORDER_TYPE_LIMIT);

//     if (trade_actions()->SendNewOrder(params) == TRADE_ACTION_RESULT_SUCCESSFUL) {
//         m_instrument_order_id_map[instrument] = params.order_id;
//     }
// }

void Team3Strategy::RepriceAll()
{
    // for (IOrderTracker::WorkingOrdersConstIter ordit = orders().working_orders_begin(); ordit != orders().working_orders_end(); ++ordit) {
    //     Reprice(*ordit);
    // }
}

void Team3Strategy::Reprice(Order* order)
{
    // OrderParams params = order->params();
    // params.price = (order->order_side() == ORDER_SIDE_BUY) ? order->instrument()->top_quote().bid() + m_aggressiveness : order->instrument()->top_quote().ask() - m_aggressiveness;
    // trade_actions()->SendCancelReplaceOrder(order->order_id(), params);
}

void Team3Strategy::OnStrategyCommand(const StrategyCommandEventMsg& msg)
{
    // switch (msg.command_id()) {
    //     case 1:
    //         RepriceAll();
    //         break;
    //     case 2:
    //         trade_actions()->SendCancelAll();
    //         break;
    //     default:
    //         logger().LogToClient(LOGLEVEL_DEBUG, "Unknown strategy command received");
    //         break;
    // }
}

void Team3Strategy::OnParamChanged(StrategyParam& param)
{    
	/*
    if (param.param_name() == "aggressiveness") {                         
        if (!param.Get(&m_aggressiveness))
            throw StrategyStudioException("Could not get m_aggressiveness");
    } else if (param.param_name() == "position_size") {
        if (!param.Get(&m_position_size))
            throw StrategyStudioException("Could not get position size");
    } else if (param.param_name() == "short_window_size") {
        if (!param.Get(&m_short_window_size))
            throw StrategyStudioException("Could not get trade size");
    } else if (param.param_name() == "long_window_size") {
        if (!param.Get(&m_long_window_size))
            throw StrategyStudioException("Could not get long_window_size");
    } else if (param.param_name() == "debug") {
        if (!param.Get(&m_debug_on))
            throw StrategyStudioException("Could not get trade size");
    } 
    */
}
