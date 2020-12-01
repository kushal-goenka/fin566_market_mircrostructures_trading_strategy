/*================================================================================
*     Source: ../RCM/StrategyStudio/includes/MarketDepthEventMsg.h
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

#ifndef _STRATEGY_STUDIO_LIB_MARKET_DEPTH_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_MARKET_DEPTH_EVENT_MSG_H_

#include "DataTypes.h"
#include "MarketDataBaseEventMsg.h"
#include "Event.h"
#include <MarketModels/DepthUpdate.h>
#include <vector>

namespace RCM {
namespace StrategyStudio {

/**
 * MarketDepthEventMsg is the event message for depth-of-book updates from an order book feed
 */
class MarketDepthEventMsg : public MarketDataBaseEventMsg {
public:
    typedef std::vector<MarketModels::DepthUpdate> DepthUpdates;
    typedef DepthUpdates::iterator DepthUpdatesIter;
    typedef DepthUpdates::const_iterator DepthUpdatesConstIter;

public:
    MarketDepthEventMsg(Event* ev, Instrument* instrument, TimeType eventTime);
    MarketDepthEventMsg(const MarketDepthEventMsg& msg);

    /**
     * Returns the instrument to which the depth update pertains
     */
    const Instrument& instrument() const { return *instrument_; }

    /**
     * Identifies the type of depth event that has occurred
     */
    MarketModels::DepthUpdateType depth_update_type() const { return depth_update_.update_type(); }
    void set_depth_update_type(MarketModels::DepthUpdateType type) {  depth_update_.set_update_type(type); }

    /**
     * Contains the details of the update to the order book
     */
    MarketModels::DepthUpdate& depth_update() { return depth_update_; }
    const MarketModels::DepthUpdate& depth_update() const { return depth_update_; }
    void set_depth_update(const MarketModels::DepthUpdate& update) { depth_update_ = update; }

    bool updated_order_book() const { return depth_update_result_.order_book_was_updated; }
    bool updated_top_quote() const { return depth_update_result_.top_quote_was_updated; }
    bool updated_market_center_best() const { return depth_update_result_.market_center_best_was_updated; }

    /**
     * Gets the market data source's timestamp for the market data event (eg the exchange feed's timestamp)
     */
    TimeType source_time() const { return depth_update_.source_time(); }

    /**
     * Gets the time the feedhandler processed the market data event, if applicable and available
     */
    TimeType feed_handler_time() const { return depth_update_.feed_handler_time(); }

    /**
     * Gets the time when the Strategy Server's data adapter received the market data event
     */
    TimeType adapter_time() const { return depth_update_.adapter_time(); }

    std::string name() const;

    MarketDepthEventMsg& operator=(const MarketDepthEventMsg& msg);

private: /* Event msg hooks */
    virtual bool PreProcess();
    virtual void PostProcess();

private:
    Instrument* instrument_;
    MarketModels::DepthUpdate depth_update_;
    MarketModels::DepthUpdateResult depth_update_result_;
};

inline std::string MarketDepthEventMsg::name() const
{
    return "MarketDepth_Instr_" + instrument_->symbol();
}

} // namespace StrategyStudio
} // namespace RCM

#endif
