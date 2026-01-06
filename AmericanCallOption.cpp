#include "AmericanCallOption.h"
#include <algorithm>
#include <stdexcept>

// Constructeur
AmericanCallOption::AmericanCallOption(double expiry, double strike)
    : AmericanOption(expiry), _strike(strike) {
    if (strike < 0) {
        throw std::invalid_argument("Strike price must be non-negative.");
    }
}

// Calcul du payoff
double AmericanCallOption::payoff(double spot) {
    return std::max(spot - _strike, 0.0);
}

// Retourne le type de l'option
OptionType AmericanCallOption::GetOptionType() {
    return OptionType::call;
}

// Getter pour le strike
double AmericanCallOption::GetOptionStrike() {
    return _strike;
}
