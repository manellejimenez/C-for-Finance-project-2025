#include "Option.h"
#include <iostream>
#include <stdexcept>

Option::Option() : _expiry(0.0) {}

Option::Option(double e) : _expiry(e)
{
    if (e < 0) {
        throw std::invalid_argument("L'échéance (expiry) ne peut pas être négative.");
    }
    std::cout << "Une option a été créée" << std::endl;
}

double Option::getExpiry() const
{
    return _expiry;
}

bool Option::isAmericanOption() {
    // Par défaut, une option n'est pas américaine (Partie 1 & 2)
    return false;
}

Option::~Option() {
    // Destructeur vide
}
