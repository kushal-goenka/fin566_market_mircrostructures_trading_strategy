/*================================================================================
*     Source: ../RCM/StrategyStudio/includes/MarketModels/IOrderBookBuilder.h
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_IORDER_BOOK_BUILDER_H_
#define _STRATEGY_STUDIO_MARKET_MODELS_IORDER_BOOK_BUILDER_H_

#include "MarketCenterTypes.h"
#include <boost/shared_ptr.hpp>

namespace RCM {
namespace StrategyStudio {
namespace MarketModels {

class IOrderBook;
class IAggrOrderBook;

/**
 * Base interface to allow custom building of order orders
 */
class IOrderBookBuilder {
public:
    IOrderBookBuilder() {}
    virtual ~IOrderBookBuilder() {}

public:
    /**
     * Creates an orderbook for the given market center
     */
    virtual IOrderBook* BuildOrderBook(MarketCenterID id) = 0;

    /**
     * Creates an aggregate order book
     */
    virtual IAggrOrderBook* BuildAggrOrderBook() = 0;
};

typedef boost::shared_ptr<IOrderBookBuilder> IOrderBookBuilderPtr;

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace RCM

#endif