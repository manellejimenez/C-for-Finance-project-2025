#pragma once
class PutOption : public EuropeanVanillaOption
{
    PutOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {}

    double payoff(double z) const
    {
        return (z <= getStrike()) ? (getStrike() - z) : 0.0;
    }

    optionType GetOptionType() const
    {
        return PUT;
    }
};