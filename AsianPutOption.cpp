#include "AsianPutOption.h"

// Constructor
AsianPutOption::AsianPutOption(std::vector<double> timeSteps, double strike) : 
    AsianOption(timeSteps, strike) {

}

// Destructor
AsianPutOption::~AsianPutOption() {}

OptionType AsianPutOption::GetOptionType() {
    return OptionType::put;
}


double AsianPutOption::payoff(double spot_prices) {
    return std::max(_strike - spot_prices, 0.0);
}