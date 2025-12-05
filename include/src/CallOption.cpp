#include "CallOption.h"
#include <algorithm> 

CallOption::CallOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike) {}

double CallOption::payoff(double z) const
{
    return std::max(z - getStrike(), 0.0);
}

EuropeanVanillaOption::optionType CallOption::GetOptionType() const
{
    return CALL;
}
