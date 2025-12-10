#include "PutOption.h"
#include <algorithm>

PutOption::PutOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike)
{
}

double PutOption::payoff(double z) const
{
    double K = getStrike();
    return std::max(K - z, 0.0);
}

optionType PutOption::GetOptionType() const
{
    return optionType::PUT;
}
