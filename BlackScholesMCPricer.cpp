#include "BlackScholesMCPricer.h"
#include <cmath>

// Constructor
BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility)
    : _option(option), _initialPrice(initial_price), _interestRate(interest_rate),
    _volatility(volatility), _nbPaths(0), _sumPayoffs(0.0), _sumPayoffsSquared(0.0) {}

int BlackScholesMCPricer::getNbPaths() const {
    return _nbPaths;
}

// Generation de nouveaux chemins

void BlackScholesMCPricer::generate(int nb_paths) {

    double expiry = _option->getExpiry();

    for (int i = 0; i < nb_paths; ++i) {

        double gaussian = MT::rand_norm();
        double exponent = (_interestRate - 0.5 * _volatility * _volatility) * expiry
            + _volatility * std::sqrt(expiry) * gaussian;
        double st = _initialPrice * std::exp(exponent);

        double payoff = 0.0;

        if (_option->isAsianOption()) {

            // Simulation du processus de diffusion aux dates d'observation pour le calcul de la moyenne
            const std::vector<double>& timeSteps = _option->getTimeSteps();
            std::vector<double> path(timeSteps.size());
            double currentTime = 0.0;
            double previousPrice = _initialPrice;

            for (size_t j = 0; j < timeSteps.size(); ++j) {
                double t = timeSteps[j];
                double dt = t - currentTime;
                gaussian = MT::rand_norm();
                exponent = (_interestRate - 0.5 * _volatility * _volatility) * dt
                    + _volatility * std::sqrt(dt) * gaussian;
                double price = previousPrice * std::exp(exponent);
                path[j] = price;
                previousPrice = price;
                currentTime = t;
            }
            payoff = _option->payoffPath(path);
        }
        else {
            // European options (not dependent on the path)
            payoff = _option->payoff(st);
        }

        double discountedPayoff = std::exp(-_interestRate * expiry) * payoff;
        _sumPayoffs += discountedPayoff;
        _sumPayoffsSquared += discountedPayoff * discountedPayoff;
    }

    _nbPaths += nb_paths;
}

// EStimation du prix xde l'option
double BlackScholesMCPricer::operator()() const {

    if (_nbPaths == 0) {
        throw std::runtime_error("No paths created");
    }

    return _sumPayoffs / _nbPaths;
}

// intervalle de confiance
std::vector<double> BlackScholesMCPricer::confidenceInterval() const {

    if (_nbPaths == 0) {
        throw std::runtime_error("No paths created");
    }

    double mean = _sumPayoffs / _nbPaths;
    double variance = (_sumPayoffsSquared / _nbPaths) - (mean * mean);
    double standardError = std::sqrt(variance / _nbPaths);
    double margin = 1.96 * standardError; 

    return { mean - margin, mean + margin };
}

// Destructor
BlackScholesMCPricer ::~BlackScholesMCPricer(){
}