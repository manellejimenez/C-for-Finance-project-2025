#include "EuropeanDigitalPutOption.h"


//Put part 
EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike) : EuropeanDigitalOption(expiry, strike) {

}

//Destructeur virtuel de la classe PutOption
EuropeanDigitalPutOption :: ~EuropeanDigitalPutOption() {

}

double EuropeanDigitalPutOption::payoff(double val) {

	if (val <= GetOptionStrike())
		return 1;
	else
		return 0;
}

//methode de la classe PutOption qui permet de retourner son type (put)
OptionType EuropeanDigitalPutOption::GetOptionType() {

	return OptionType::put;
}

