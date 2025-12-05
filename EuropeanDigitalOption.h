#pragma once
#include "Option.h"

class EuropeanDigitalOption : public Option {
private:
    double _strike;

public:
    EuropeanDigitalOption(double expiry, double strike);

    double getStrike() const;

    // Reste pure virtuelle
    virtual double payoff(double z) = 0;

    virtual ~EuropeanDigitalOption() {};
};

class EuropeanDigitalCallOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalCallOption(double expiry, double strike);
    double payoff(double z) override;
};

class EuropeanDigitalPutOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalPutOption(double expiry, double strike);
    double payoff(double z) override;
};
