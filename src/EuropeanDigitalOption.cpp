#include "EuropeanDigitalOption.h"

EuropeanDigitalOption::EuropeanDigitalOption(double expiry, double strike)
    : Option(expiry), _strike(strike) {}

double EuropeanDigitalOption::getStrike() const { return _strike; }

EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {}

double EuropeanDigitalCallOption::payoff(double z) const {
    return (z >= getStrike()) ? 1.0 : 0.0;
}

optionType EuropeanDigitalCallOption::GetOptionType() const {
    return optionType::CALL;
}

EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {}

double EuropeanDigitalPutOption::payoff(double z) const {
    return (getStrike() >= z) ? 1.0 : 0.0;
}

optionType EuropeanDigitalPutOption::GetOptionType() const {
    return optionType::PUT;
}
