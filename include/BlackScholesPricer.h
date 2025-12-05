#pragma once
#include "EuropeanVanillaOption.h"

class BlackScholesPricer
{
private:
    EuropeanVanillaOption* _option;
    double _asset_price;
    double _interest_rate;
    double _volatility;

public:
    BlackScholesPricer(EuropeanVanillaOption* option,
                       double asset_price,
                       double interest_rate,
                       double volatility);

    double norm_cdf(double x) const;
    double price() const;
    double delta() const;
};
