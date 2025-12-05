#include "Option.h"
#include <iostream>
#include <stdexcept>


Option::Option() : _expiry(0.0) {}


Option::Option(double e) : _expiry(e)
{
    std::cout << "Une option a été créée" << std::endl;
}

Option::~Option() = default;


double Option::getExpiry() const
{
    return _expiry;
}

