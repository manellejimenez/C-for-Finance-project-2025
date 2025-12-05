#pragma once
#include "Option.h"
#include <stdexcept>

class EuropeanVanillaOption : public Option
{
protected:
    double _strike;

public:
    enum optionType { CALL, PUT };

    EuropeanVanillaOption();
    EuropeanVanillaOption(double expiry, double strike);

    double getStrike() const;

    virtual optionType GetOptionType() const = 0;
};

// Classe finale pour le CALL
class CallOption : public EuropeanVanillaOption {
public:
    CallOption(double expiry, double strike);
    double payoff(double z) override;
};

// Classe finale pour le PUT
class PutOption : public EuropeanVanillaOption {
public:
    PutOption(double expiry, double strike);
    double payoff(double z) override;
};
