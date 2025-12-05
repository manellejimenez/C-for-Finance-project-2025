#pragma once
#include "Option.h"
#include <stdexcept>

class EuropeanVanillaOption : public Option
{
private:
    double _strike;

public:
    enum optionType { CALL, PUT };

    EuropeanVanillaOption();
    EuropeanVanillaOption(double expiry, double strike);

    double getStrike() const;

    virtual optionType GetOptionType() const = 0;
};
