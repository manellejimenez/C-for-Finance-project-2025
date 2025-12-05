#include "EuropeanVanillaOption.h"
#include <stdexcept>


EuropeanVanillaOption::EuropeanVanillaOption() : Option(), _strike(0.0) {}


EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike)
    : Option(expiry), _strike(strike)
{
    if (expiry < 0 || strike < 0)
        throw std::invalid_argument("Expiry et strike doivent être non-négatifs");
}


double EuropeanVanillaOption::getStrike() const
{
    return _strike;
}



