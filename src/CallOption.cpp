#include "CallOption.h"
#include <algorithm>

CallOption::CallOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike)
{
}

double CallOption::payoff(double z) const
{
    double K = getStrike();
    return std::max(z - K, 0.0);
}

optionType CallOption::GetOptionType() const
{
    return optionType::CALL;
}
