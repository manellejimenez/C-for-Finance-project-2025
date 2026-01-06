#include "AmericanPutOption.h"
#include <algorithm>
#include <stdexcept>

// Constructeur
AmericanPutOption::AmericanPutOption(double expiry, double strike)
    : AmericanOption(expiry), _strike(strike) {
    if (strike < 0) {
        throw std::invalid_argument("Strike price must be non-negative.");
    }
}

// Calcul du payoff
double AmericanPutOption::payoff(double spot) {
    return std::max(_strike - spot, 0.0);
}

// Retourne le type de l'option
OptionType AmericanPutOption::GetOptionType() {
    return OptionType::put;
}

// Getter pour le strike
double AmericanPutOption::GetOptionStrike() {
    return _strike;
}
