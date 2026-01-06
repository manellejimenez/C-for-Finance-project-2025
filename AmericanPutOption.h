#pragma once
#include "AmericanOption.h"

class AmericanPutOption : public AmericanOption {
private:
    double _strike;

public:
    // Constructeur
    AmericanPutOption(double expiry, double strike);

    // Surcharge des methodes
    double payoff(double spot) override;
    OptionType GetOptionType() override;
    double GetOptionStrike() override;
};
