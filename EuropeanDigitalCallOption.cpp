#include "EuropeanDigitalCallOption.h"


//Call part
EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike) : EuropeanDigitalOption(expiry, strike) {

}

//Destructeur virtuel de la classe EuropeanDigitalCallOption
EuropeanDigitalCallOption :: ~EuropeanDigitalCallOption() {

}

double EuropeanDigitalCallOption::payoff(double price_function) {

	if (price_function >= GetOptionStrike())
		return 1;
	else
		return 0;
}

//Definition de la methode de la classe CallOption qui permet de retourner son type(call)
OptionType EuropeanDigitalCallOption::GetOptionType() {

	//return le type de l'option encapsulee dans le optiontype enum
	return OptionType::call;
}

