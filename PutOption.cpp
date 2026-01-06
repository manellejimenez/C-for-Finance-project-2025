#include "PutOption.h"

//Put part 
PutOption::PutOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {

}

//Destructeur virtuel de la classe PutOption
PutOption :: ~PutOption() {

}

double PutOption::payoff(double price_function) {

	return std::max(GetOptionStrike() - price_function, 0.0);
}

//D�finition de la m�thode de la classe PutOption qui permet de retourner son type (put)
OptionType PutOption::GetOptionType() {

	return OptionType::put;
}
