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

    // Redéfinition de la méthode virtuelle pour dire que l'option est Américaine
    bool isAmericanOption() override;

    // Destructeur virtuel
    virtual ~AmericanOption() {};
};

class AmericanCallOption : public AmericanOption {
public:
    AmericanCallOption(double expiry, double strike);

    // Implémentation du payoff
    double payoff(double z) override;
};

class AmericanPutOption : public AmericanOption {
public:
    AmericanPutOption(double expiry, double strike);

    // Implémentation du payoff
    double payoff(double z) override;
};
