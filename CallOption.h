#pragma once
class CallOption : public EuropeanVanillaOption
{
public:
    CallOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {}

    double payoff(double z) const
    {
        return (z >= getStrike()) ? (z - getStrike()) : 0.0;
    }

    optionType GetOptionType() const
    {
        return CALL;
    }
};

