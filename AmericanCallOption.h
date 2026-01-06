#pragma once
#include "AmericanOption.h"

class AmericanCallOption : public AmericanOption {
private:
    double _strike;

public:
    // Constructeur
    AmericanCallOption(double expiry, double strike);

    // Surcharge des methodes
    double payoff(double spot) override;
    OptionType GetOptionType() override;
    double GetOptionStrike() override;
};
