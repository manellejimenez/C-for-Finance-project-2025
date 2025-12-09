#include "PutOption.h"
#include <algorithm>


PutOption::PutOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike) {}


double PutOption::payoff(double z) const
{
    return std::max(getStrike() - z, 0.0);
}


EuropeanVanillaOption::optionType PutOption::GetOptionType() const
{
    return PUT;
}
