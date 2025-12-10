#pragma once
#include "Option.h"

// Déclaration anticipée
class BlackScholesPricer;

// --- CLASSE MÈRE ---
class EuropeanDigitalOption : public Option {
    friend class BlackScholesPricer;
private:
    double _strike;

public:
    EuropeanDigitalOption(double expiry, double strike);
    double getStrike() const;

    // Méthode pure virtuelle (abstraite)
    virtual optionType GetOptionType() const = 0;

    virtual double payoff(double z) const = 0;
    virtual ~EuropeanDigitalOption() = default;
};

// --- CLASSE FILLE : CALL ---
class EuropeanDigitalCallOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalCallOption(double expiry, double strike);

    double payoff(double z) const override;

    // C'EST CETTE LIGNE QUI MANQUAIT :
    optionType GetOptionType() const override;
};

// --- CLASSE FILLE : PUT ---
class EuropeanDigitalPutOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalPutOption(double expiry, double strike);

    double payoff(double z) const override;

    // CELLE-CI MANQUAIT AUSSI :
    optionType GetOptionType() const override;
};
