/*================================================================================
*     Source: ../RCM/StrategyStudio/includes/MarketModels/Quote.h
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_QUOTE_H_
#define _STRATEGY_STUDIO_MARKET_MODELS_QUOTE_H_

#include "QuoteSide.h"
#include "ConditionCodes.h"
#include "MDBaseObject.h"

namespace RCM {
namespace StrategyStudio {
namespace MarketModels {

/**
 * Quote consists of a paired bid entry and an ask entry
 *
 * This class is used as the base for quote data for market centers, quotes for market participants
 * and quote summaries such as TopQuote (sum of liquidity from quotes at best prices), and NBBO quotes
 * (the bid and offer from the 'best' exchange on each side, typically determined by something like a
 * price, size, time priority rule)
 */
class Quote {
public:
    Quote();
    Quote(const QuoteSide& bidEntry, const QuoteSide& askEntry);
    Quote(double bidPrice, int bidSize, double askPrice, int askSize);
    Quote(double bidPrice, int bidSize, double askPrice, int askSize, QuoteCondition cond);

    Quote(double bidPrice, int bidSize, double askPrice, int askSize,
          TimeType bidSourceTime, TimeType bidFeedHandlerTime,
          TimeType askSourceTime, TimeType askFeedHandlerTime, TimeType adapterTime);

    Quote(double bidPrice, int bidSize, double askPrice, int askSize, QuoteCondition cond,
          TimeType bidSourceTime, TimeType bidFeedHandlerTime,
          TimeType askSourceTime, TimeType askFeedHandlerTime, TimeType adapterTime);

    Quote(const Quote& quote);

    virtual ~Quote();

    /**
     * Gets the bid price of the quote
     */
    double bid() const { return m_bidEntry.price(); }
    void set_bid(double price) { m_bidEntry.set_price(price); }

    /**
     * Gets the ask/offer price of the quote
     */
    double ask() const { return m_askEntry.price(); }
    void set_ask(double price) { m_askEntry.set_price(price); }

    /**
     * Gets the size of the bid
     */
    int bid_size() const { return m_bidEntry.size(); }
    void set_bid_size(int size) { m_bidEntry.set_size(size); }

    /**
     * Gets the size of the ask
     */
    int ask_size() const { return m_askEntry.size(); }
    void set_ask_size(int size) { m_askEntry.set_size(size); }

    QuoteSide& bid_side() { return m_bidEntry; }

    /**
     * Gets the bid side of the quote as an order book entry
     */
    const QuoteSide& bid_side() const { return m_bidEntry; }

    QuoteSide& ask_side() { return m_askEntry; }

    /**
     * Gets the ask side of the quote as an order book entry
     */
    const QuoteSide& ask_side() const { return m_askEntry; }

    /**
     * Gets the market data source's timestamp for the bid quote side
     */
    TimeType bid_source_time() const { return m_bidEntry.source_time(); }
    void set_bid_source_time(TimeType time) { m_bidEntry.set_source_time(time); }

    /**
     * Gets the time the feedhandler processed the market data event, if applicable and available
     */
    TimeType bid_feed_handler_time() const { return m_bidEntry.feed_handler_time(); }
    void set_bid_feed_handler_time(TimeType time) { m_bidEntry.set_feed_handler_time(time);  }

    /**
     * Gets the local server time when Strategy Studio received the market data event
     */
    TimeType bid_adapter_time() const { return m_bidEntry.adapter_time(); }
    void set_bid_adapter_time(TimeType time) { m_bidEntry.set_adapter_time(time); }

    /**
     * Gets the market data source's timestamp for the bid quote side
     */
    TimeType ask_source_time() const { return m_askEntry.source_time(); }
    void set_ask_source_time(TimeType time) { m_askEntry.set_source_time(time); }

    /**
     * Gets the time the feedhandler processed the market data event, if applicable and available
     */
    TimeType ask_feed_handler_time() const { return m_askEntry.feed_handler_time(); }
    void set_ask_feed_handler_time(TimeType time) { m_askEntry.set_feed_handler_time(time);  }

    /**
     * Gets the local server time when Strategy Studio received the market data event
     */
    TimeType ask_adapter_time() const { return m_askEntry.adapter_time(); }
    void set_ask_adapter_time(TimeType time) { m_askEntry.set_adapter_time(time); }

    /**
     * Get the mid-price of the quote
     */
    double mid_price() const;

    /**
     * Gets a weighted mid-price, where the price is weighted
     * by the quote size on the oposite side of the market
     *
     * Returns NaN if both bid and ask sizes are zero
     */
    double micro_price() const;

    /**
     * Get the spread associated with the quote
     */
    double spread() const;

    /**
     * Gets the condition of the quote
     *
     * Quote conditions describe the status of the quote, indicating for instance
     * whether the quote is firm, is immediately executable, is halted, or is being
     * updated abnormally
     */
    QuoteCondition condition() const { return m_quoteCondition; }
    void set_condition(QuoteCondition cond) { m_quoteCondition = cond; }

    /**
     * Check if the market is crossed with bid price above ask price
     */
    bool IsCrossed() const;

    /**
     * Checks both bid and ask if they are valid (price and size non-zero) and not crossed
     */
    bool IsValid() const;

    /**
     * Checks if bid side is valid (price and size non-zero)
     */
    bool IsBidValid() const;

    /**
     * Checks if ask side is valid (price and size non-zero)
     */
    bool IsAskValid() const;

    /**
     * Checks if bid side is subject to Reg NMS or options market trade through protections
     */
    bool IsBidTradeThroughProtected() const;

    /**
     * Checks if ask side is subject to Reg NMS or options market trade through protections
     */
    bool IsAskTradeThroughProtected() const;

    bool IsBidFirm() const;

    bool IsAskFirm() const;

    bool IsConditionHalted() const;

    /**
     * Verifies that quote has non-zero price and size
     */
    bool IsSet() const;

    /**
     * Check if quote is has non zero prices or sizes
     */
    bool HasData() const;

    /**
     * Reset prices
     */
    void ResetPrices();

    /**
     * Update the relevant fields for the quote
     */
    void UpdateQuote(const Quote& quote);

    /**
     * Update the relevant fields for the quote
     */
    void UpdateQuote(double bidPrice,
                     int bidSize,
                     double askPrice,
                     int askSize,
                     TimeType bidSourceTime,
                     TimeType bidFeedHandlerTime,
                     TimeType askSourceTime,
                     TimeType askFeedHandlerTime,
                     TimeType adapterTime);

    /**
     * Only updates the times
     */
    void UpdateTimes(const Quote& quote);

    bool operator==(const Quote& quote) const;

    Quote& operator=(const Quote& quote);

private:
    QuoteSide m_bidEntry;
    QuoteSide m_askEntry;
    QuoteCondition m_quoteCondition;
};

inline double Quote::mid_price() const
{
    return (m_bidEntry.price() + m_askEntry.price()) / 2.0;
}

inline double Quote::micro_price() const
{
    return (m_bidEntry.price() * m_askEntry.size() + m_askEntry.price() * m_bidEntry.size()) / static_cast<double>(m_bidEntry.size() + m_askEntry.size());
}

inline double Quote::spread() const
{
    return (m_askEntry.price() - m_bidEntry.price());
}

inline bool Quote::IsCrossed() const
{
    return m_bidEntry.price() > m_askEntry.price();
}

inline bool Quote::IsValid() const
{
    // DESIGN: Should we make locked markets valid???
    return (m_bidEntry.IsValid() &&
            m_askEntry.IsValid() &&
            (m_bidEntry.price() <= m_askEntry.price()) // crossed market invalid
            );
}

inline bool Quote::IsBidValid() const
{
    return m_bidEntry.IsValid();
}

inline bool Quote::IsAskValid() const
{
    return m_askEntry.IsValid();
}

inline bool Quote::IsSet() const
{
    return (m_bidEntry.IsValid() && m_askEntry.IsValid());
}

inline bool Quote::HasData() const
{
    return (m_bidEntry.HasData() || m_askEntry.HasData());
}

inline std::ostream& operator<<(std::ostream& out, const Quote& quote)
{
    out << "BID: " << quote.bid_side()
        << " ASK: " << quote.ask_side()
        << " cond: " << QuoteConditionUtil::QuoteConditionToString(quote.condition());

    return out;
}

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace RCM

#endif