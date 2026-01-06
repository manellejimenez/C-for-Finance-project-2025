#include "AsianOption.h"
#include <numeric>

//Constructor
AsianOption::AsianOption(std::vector<double> timeSteps, double strike) : Option(timeSteps.back()) {

    if (strike <= 0) {
        throw std::invalid_argument("Strike must be positive");
    }
    else {

        _timeSteps = timeSteps;
        _strike = strike;
    }
}

// Destructor
AsianOption::~AsianOption() {}

// Retourne le time steps de l'option
std::vector<double> AsianOption::getTimeSteps() {
    return _timeSteps;
}

// Retourne le payoff d'un chemin
double AsianOption::payoffPath(std::vector<double> spot_prices) {

    long size = spot_prices.size();
    double somme = 0;

    for (int i = 0; i < size; i++) {
        somme += spot_prices.at(i);
    }

    double mean = somme / size;

    return payoff(mean);

}

double AsianOption::GetOptionStrike() {
    return _strike;
}

bool AsianOption::isAsianOption() {
    return true;
}