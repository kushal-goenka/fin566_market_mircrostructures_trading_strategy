/*================================================================================
*     Source: ../RCM/StrategyStudio/includes/MarketModels/Future.h
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_FUTURE_H_
#define _STRATEGY_STUDIO_MARKET_MODELS_FUTURE_H_

#include "Instrument.h"
#include "DerivativesTypes.h"
#include <string>
#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace RCM {
namespace StrategyStudio {
namespace MarketModels {

/**
 * Instrument represents a futures contract
 */
class Future : public Instrument {
public:
    Future(InstrumentID instrID,
           const SymbolTag& symbol,
           MarketType marketType,
           const Markets::MarketCenterIDCollection& marketCenterIDs,
           IOrderBookBuilderPtr pOrderBookBuilder,
           MarketCenterInfoFactory* marketCenterInfoFactory);

    virtual ~Future();

    /**
     * Returns the root symbol (product code) of the instrument
     */
    const SymbolTag& root_symbol() const { return m_rootSymbol; }
    void set_root_symbol(const SymbolTag& rootSymbol) { m_rootSymbol = rootSymbol; }

    /**
     * Retrieves the expiration date of the futures contract
     */
    boost::gregorian::date expiry_date() const { return m_expiryDate; }
    void set_expiry_date(boost::gregorian::date expiryDate) { m_expiryDate = expiryDate; }

    /**
     * Retrieves the minimum tick size for trading calendar spreads in the futures product
     */
    double spread_tick_size() const { return m_fSpreadTickSize; }
    void set_spread_tick_size(double tickSize) { m_fSpreadTickSize = tickSize; }

    /**
     * Retrieves the settlement/delivery style for the futures product
     */
    DeliveryType type_of_delivery() { return m_deliveryType; }
    void set_type_of_delivery(DeliveryType type) { m_deliveryType = type; }

    /**
     * Retrieves the initial margin requirement for speculators in the futures product
     */
    double initial_margin() const { return m_fInitialMargin; }
    void set_initial_margin(double margin) { m_fInitialMargin = margin; }

    /**
     * Retrieves the maintenance margin requirement for speculators in the futures product
     */
    double maintenance_margin() const { return m_fMaintenanceMargin; }
    void set_maintenance_margin(double margin) { m_fMaintenanceMargin = margin; }

    /**
     * Retrieves the initial margin requirement for members or hedgers
     */
    double member_initial_margin() const { return m_fMemberInitialMargin; }
    void set_member_initial_margin(double margin) { m_fMemberInitialMargin = margin; }

    /**
     * Retrieves the maintenance margin requirement for members or hedgers
     */
    double member_maintentance_margin() const { return m_fMemberMaintenanceMargin; }
    void set_member_maintenance_margin(double margin) { m_fMemberMaintenanceMargin = margin; }

    const void* external_properties() const { return m_extProperties; }
    void set_external_properties(void* extProperties);

    bool operator==(const Future& future) const;

private:
    Future(const Future& future); // not implemented
    Future& operator=(const Future& future); // not implemented

protected:
    SymbolTag m_rootSymbol;
    boost::gregorian::date m_expiryDate;
    double m_fSpreadTickSize;
    double m_fInitialMargin;
    double m_fMaintenanceMargin;
    double m_fMemberInitialMargin;
    double m_fMemberMaintenanceMargin;
    void* m_extProperties;
    DeliveryType m_deliveryType;
};

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace RCM

#endif