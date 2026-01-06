#include "AsianCallOption.h"
#include "Option.h"

// Constructor
AsianCallOption::AsianCallOption(std::vector<double> timeSteps, double strike) : 
    AsianOption(timeSteps, strike) {

}

AsianCallOption::~AsianCallOption() {}

OptionType AsianCallOption::GetOptionType() {
    return OptionType::call;
}

double AsianCallOption::payoff(double spot_prices) {
    return std::max(spot_prices - _strike, 0.0);
}