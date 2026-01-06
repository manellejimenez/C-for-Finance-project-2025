#include "EuropeanVanillaOption.h"
#include <iostream>

//Constructeur qui appelle constructeur de base de Option et test si les parametres sont nuls
EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike) : Option(expiry), _strike(strike)
{
	if (strike <= 0 || expiry <= 0)
		std::cout << "The arguments : " << strike << " and/or " << expiry << "are/is negative(s)";
}

//Destructeur virtuel
EuropeanVanillaOption:: ~EuropeanVanillaOption() {

}

//Permet d'obtenir l'attribut priv� de l'option
double EuropeanVanillaOption::GetOptionStrike() {
	return _strike;
}



