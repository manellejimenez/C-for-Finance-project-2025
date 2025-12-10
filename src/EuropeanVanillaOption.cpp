#include "EuropeanVanillaOption.h"
#include <stdexcept>

EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike)
    : Option(expiry), _strike(strike)
{
    if (expiry < 0 || strike < 0) {
        throw std::invalid_argument("Expiry et Strike doivent être positifs ou nuls.");
    }
}

double EuropeanVanillaOption::getStrike() const {
    return _strike;
}



