#pragma once
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"

class BlackScholesPricer
{
private:
    // On garde des pointeurs vers l'option à pricer
    // Un seul des deux sera non-nul
    EuropeanVanillaOption* _optionVanilla;
    EuropeanDigitalOption* _optionDigital;

    double _asset_price; // S0
    double _interest_rate; // r
    double _volatility; // sigma

    // Méthode privée utilitaire pour la fonction de répartition normale cumulée
    double cdf(double x) const;
    // Méthode privée pour la densité de probabilité normale (pour le delta digital)
    double pdf(double x) const;

public:
    // Constructeur pour Vanilla
    BlackScholesPricer(EuropeanVanillaOption* option, double asset_price, double interest_rate, double volatility);

    // Constructeur surchargé pour Digital
    BlackScholesPricer(EuropeanDigitalOption* option, double asset_price, double interest_rate, double volatility);

    // Opérateur() qui retourne le prix
    double operator()() const;

    // Méthode delta
    double delta() const;
};
