#pragma once
#include "EuropeanVanillaOption.h"

class CallOption : public EuropeanVanillaOption
{
public:
    CallOption(double expiry, double strike);

    double payoff(double z) override;
    optionType GetOptionType() const override;
};
