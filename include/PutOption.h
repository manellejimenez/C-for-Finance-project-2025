#pragma once
#include "EuropeanVanillaOption.h"

class PutOption : public EuropeanVanillaOption
{
public:
    PutOption(double expiry, double strike);

    double payoff(double z) const override;

    optionType GetOptionType() const override;

    virtual ~PutOption() = default;
};
