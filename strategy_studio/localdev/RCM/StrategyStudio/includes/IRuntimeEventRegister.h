/*================================================================================
*     Source: ../RCM/StrategyStudio/includes/IRuntimeEventRegister.h
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

#ifndef _STRATEGY_STUDIO_LIB_IRUN_EVENTREGISTER_H_
#define _STRATEGY_STUDIO_LIB_IRUN_EVENTREGISTER_H_

#include "IEventRegister.h"
#include <boost/any.hpp>

namespace RCM {
namespace StrategyStudio {

/**
 * This interface class is the event registration interface that strategies use
 * to register for runtime events. It extendes the base event reigistraion.
 */
class IRuntimeEventRegister : public IEventRegister {
public:
    IRuntimeEventRegister() {}
    virtual ~IRuntimeEventRegister() {}

public: /* Runtime event registration */

    /**
     * Used to send strategy notification event messages between strategies
     * @returns true if event msg scheduled for sending, false if target doesn't exist
     */
    virtual bool SendMessageToStrategy(IEventRequester* strategy,
                                                 const std::string& target,
                                                 const std::string& msg)=0;

    /**
     * Used to send strategy notification event messages between strategies with closure
     * @returns true if event msg scheduled for sending, false if target doesn't exist
     */
    virtual bool SendMessageToStrategy(IEventRequester* strategy,
                                                 const std::string& target,
                                                 const std::string& msg,
                                                 void* closure)=0;

    /**
     * Publishes a message to a given topic
     */
    virtual bool SendMessageToTopic(IEventRequester* strategy,
                                    const std::string& topic,
                                    const std::string& msg,
                                    const boost::any& closure = boost::any())=0;

    /**
     * Used to send an exogenous fill to a specified strategy.
     *
     * Like with reporting external fills via command line or Strategy Manager, this will update
     * target strategy's positions and trigger OnExternalFill. Target strategy must be able to subscribe to specified symbol.
     *
     * @returns true if event msg scheduled for sending, false if target strategy doesn't exist or if it can't subscribe to the symbol
     */
    virtual bool SendExternalFillToStrategy(IEventRequester* requester,
                                            const std::string& target,
                                            const std::string& symbol,
                                            int size,
                                            double price,
                                            MarketCenterID market,
                                            bool applyFees)=0;

};

} // namespace StrategyStudio
} // namespace RCM

#endif
