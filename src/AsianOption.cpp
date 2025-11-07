#include "AsianOption.h"

AsianOption::AsianOption(const std::vector<double>& timeSteps_, double K_)
    : Option(K_), timeSteps(timeSteps_) {}

double AsianOption::payoffPath(const std::vector<double>& path) const {
    double sum = std::accumulate(path.begin(), path.end(), 0.0);
    double mean = sum / path.size();
    return payoff(mean); // appelle payoff(double) de la classe dérivée
}
