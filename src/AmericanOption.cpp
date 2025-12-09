#include "AmericanOption.h"
#include <algorithm> // Nécessaire pour std::max

// --- AmericanOption ---

AmericanOption::AmericanOption(double expiry, double strike)
    : Option(expiry), _strike(strike) {
}

double AmericanOption::getStrike() const {
    return _strike;
}

bool AmericanOption::isAmericanOption() {
    return true; // C'est le marqueur important pour le CRRPricer
}

// --- AmericanCallOption ---

AmericanCallOption::AmericanCallOption(double expiry, double strike)
    : AmericanOption(expiry, strike) {
}

double AmericanCallOption::payoff(double z) {
    // Payoff d'un Call : Max(S - K, 0)
    return std::max(z - getStrike(), 0.0);
}

// --- AmericanPutOption ---

AmericanPutOption::AmericanPutOption(double expiry, double strike)
    : AmericanOption(expiry, strike) {
}

double AmericanPutOption::payoff(double z) {
    // Payoff d'un Put : Max(K - S, 0)
    return std::max(getStrike() - z, 0.0);
}
