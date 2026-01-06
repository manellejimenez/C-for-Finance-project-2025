#include "EuropeanDigitalOption.h"

//Consteucteur 
EuropeanDigitalOption::EuropeanDigitalOption(double expiry, double strike) : Option(expiry), _strike(strike) {

	if (strike <= 0 || expiry <= 0)
		std::cout << "The arguments : " << strike << " and/or " << expiry << "are/is negative(s)";
	else
		_strike = strike;
}


//Destructeur virtuel
EuropeanDigitalOption:: ~EuropeanDigitalOption() {

}

//Permet d'obtenir l'attribut priver de l'option
double EuropeanDigitalOption::GetOptionStrike() {
	return _strike;
}

bool EuropeanDigitalOption::isDigital() {
	return true;
}