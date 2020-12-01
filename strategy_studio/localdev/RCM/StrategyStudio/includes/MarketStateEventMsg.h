/*================================================================================
*     Source: ../RCM/StrategyStudio/includes/MarketStateEventMsg.h
*     Last Update: 2010/09/30 13:55:14
*     Contents:
*     Distribution:
*
*
*     Copyright (c) RCM-X, 2009 - 2010.
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
==================================================================================*/

#pragma once

#ifndef _STRATEGY_STUDIO_LIB_MARKET_STATE_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_MARKET_STATE_EVENT_MSG_H_

#include "TimePrioritizedEventMsg.h"
#include "DataTypes.h"
#include "DataTypesUtils.h"
#include "Event.h"

namespace RCM {
namespace StrategyStudio {

enum MarketStateMsgType {
    MARKET_STATE_MSG_TYPE_UNKNOWN = -1,
    MARKET_STATE_MSG_TYPE_CHANGE = 0,    // implies market state has transitioned
    MARKET_STATE_MSG_TYPE_SNAPSHOT = 1   // snapshot of current value of market
};

/**
 * MarketStateEventMsg informs strategies when market has opened/closed or the
 * current state of the market.
 */
class MarketStateEventMsg : public TimePrioritizedEventMsg {
public:
    static const int TIMED_EVENT_PRIORITY = 8;

public:

    MarketStateEventMsg(MarketStateMsgType type, MarketState state, Event* ev);

    MarketStateEventMsg(MarketStateMsgType type, TimeType fireTime, MarketState state, Event* ev);

    MarketStateEventMsg(const MarketStateEventMsg& msg);

    ~MarketStateEventMsg();

    std::string name() const;

    MarketStateMsgType message_type() const { return m_msgType; }
    void set_message_type(MarketStateMsgType type) { m_msgType = type; }

    MarketState market_state() const { return m_state; }
    void set_market_state(MarketState state) { m_state = state; }

    bool IsSnapshot() const { return (m_msgType == MARKET_STATE_MSG_TYPE_SNAPSHOT); }

    bool Trigger(TimeType currTime);

    MarketStateEventMsg& operator=(const MarketStateEventMsg& msg);

private:
    MarketStateMsgType m_msgType;
    MarketState m_state;
};

inline std::string MarketStateEventMsg::name() const
{
    return "MarketState_" + DataTypesUtils::MarketStateToString(m_state);
}

} // namespace StrategyStudio
} // namespace RCM

#endif