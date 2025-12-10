#pragma once
#include "Option.h"

//enum class optionType { CALL, PUT };
class BlackScholesPricer;
class EuropeanVanillaOption : public Option
{
//BlackScholesPricer as a friend class
    friend class BlackScholesPricer;

private:
    double _strike;

public:
    EuropeanVanillaOption(double expiry, double strike);

    // Getter nécessaire pour les classes filles (car _strike est privé)
    double getStrike() const;

    // Consigne : "pure virtual method GetOptionType()"
    virtual optionType GetOptionType() const = 0;

    // Destructeur virtuel par défaut
    virtual ~EuropeanVanillaOption() = default;
};


