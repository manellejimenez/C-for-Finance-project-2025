#include "EuropeanVanillaOption.h"
#include <algorithm> // Pour std::max

// --- Mère ---
EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike) 
    : Option(expiry), _strike(strike) {
}

double EuropeanVanillaOption::getStrike() const {
    return _strike;
}

// --- CallOption (Vanilla) ---
CallOption::CallOption(double expiry, double strike) 
    : EuropeanVanillaOption(expiry, strike) {
}

double CallOption::payoff(double z) {
    // Max(S - K, 0)
    return std::max(z - getStrike(), 0.0);
}

// --- PutOption (Vanilla) ---
PutOption::PutOption(double expiry, double strike) 
    : EuropeanVanillaOption(expiry, strike) {
}

double PutOption::payoff(double z) {
    // Max(K - S, 0)
    return std::max(getStrike() - z, 0.0);
}



