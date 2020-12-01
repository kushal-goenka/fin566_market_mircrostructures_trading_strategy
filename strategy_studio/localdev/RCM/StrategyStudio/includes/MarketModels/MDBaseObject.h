/*================================================================================
*     Source: ../RCM/StrategyStudio/includes/MarketModels/MDBaseObject.h
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_MD_BASE_OBJECT_H_
#define _STRATEGY_STUDIO_MARKET_MODELS_MD_BASE_OBJECT_H_

#include <Utilities/TimeType.h>

namespace RCM {
namespace StrategyStudio {
namespace MarketModels {

using RCM::StrategyStudio::Utilities::TimeType;

/**
 * MDBaseObject is a base object for market data objects. It contains objects
 * common to all market data objects.
 */
class MDBaseObject {
public:
    MDBaseObject();

    MDBaseObject(TimeType sourceTime,
                 TimeType feedHandlerTime,
                 TimeType adapterTime);

    MDBaseObject(const MDBaseObject& mdBaseObject);

    virtual ~MDBaseObject();

    /**
     * Gets the market data source's timestamp for the market data event (eg the exchange feed's timestamp)
     */
    TimeType source_time() const { return m_sourceTime; }
    void set_source_time(TimeType time) { m_sourceTime = time; }

    /**
     * Gets the time the feedhandler processed the market data event, if applicable and available
     */
    TimeType feed_handler_time() const { return m_feedHandlerTime; }
    void set_feed_handler_time(TimeType time) { m_feedHandlerTime = time; }

    /**
     * Gets the time when the Strategy Server's data adapter received the market data event
     */
    TimeType adapter_time() const { return m_adapterTime; }
    void set_adapter_time(TimeType time) { m_adapterTime = time; }

    /**
     * Reset all times to default values
     */
    void ResetTimes();

    MDBaseObject& operator=(const MDBaseObject& rhs);

protected:
    TimeType m_sourceTime;
    TimeType m_feedHandlerTime;
    TimeType m_adapterTime;
};

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace RCM

#endif