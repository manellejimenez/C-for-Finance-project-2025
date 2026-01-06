#include "CallOption.h"


//Part 3
//constructeurs des classes cal et put heritants des attributs de la Euvanillaoption

//Call part
CallOption::CallOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {

}

//Destructeur virtuel de la classe CallOption
CallOption :: ~CallOption() {

}

double CallOption::payoff(double price_function) {

	return std::max(price_function - GetOptionStrike(), 0.0);
}

//Definition de la methode de la classe CallOption qui permet de retourner son type (call)
OptionType CallOption::GetOptionType() {

	return OptionType::call;
}
