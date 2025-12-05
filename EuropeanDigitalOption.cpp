#include "EuropeanDigitalOption.h"

EuropeanDigitalOption::EuropeanDigitalOption(double expiry, double strike)
    : Option(expiry), _strike(strike) {
}

double EuropeanDigitalOption::getStrike() const {
    return _strike;
}

//Call Digital
EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {
}

double EuropeanDigitalCallOption::payoff(double z) {
    if (z >= getStrike()) return 1.0;
    return 0.0;
}

//Put Digital
EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {
}

double EuropeanDigitalPutOption::payoff(double z) {
    if (z <= getStrike()) return 1.0;
    return 0.0;
}
