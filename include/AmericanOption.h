#pragma once
#include "Option.h"

class AmericanOption : public Option {
private:
    double _strike;

public:
    // Constructeur
    AmericanOption(double expiry, double strike);

    // Getters
    double getStrike() const;

    // Redéfinition de la méthode virtuelle
    bool isAmericanOption() override;

    // Destructeur virtuel
    virtual ~AmericanOption() = default;
};

class AmericanCallOption : public AmericanOption {
public:
    AmericanCallOption(double expiry, double strike);

    double payoff(double z) const override;
};

class AmericanPutOption : public AmericanOption {
public:
    AmericanPutOption(double expiry, double strike);

    double payoff(double z) const override;
};


