#include "Option.h"
#include <stdexcept> 

Option::Option(double expiry) : _expiry(expiry) {
	if (expiry < 0) {
		throw std::invalid_argument("Expiry must be non-negative.");
	}
	else
		_expiry = expiry;
}

//Getter method
double Option::getExpiry() {
return _expiry;
}

double Option::payoff(double) {
	return 0;
}

// Return the payoff of the last spot prices
double Option::payoffPath(std::vector<double> spot_prices) {
	return payoff(spot_prices.at(spot_prices.size() - 1));
}

std::vector<double> Option::getTimeSteps() {
	std::vector<double> timesteps{ 0, _expiry };
	return timesteps;
}

bool Option::isDigital() {
	return false;
}

bool Option:: isAsianOption()
{
	return false;
}

// Check if it's an American Option
bool Option :: isAmericanOption()
{
	return false;
}

// Destructeur virtuel
Option :: ~Option() {
}



