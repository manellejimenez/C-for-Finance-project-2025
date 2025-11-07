#include "BlackScholesMCPricer.h"
#include "AsianOption.h"
#include <numeric>
#include <algorithm>

BlackScholesMCPricer::BlackScholesMCPricer(Option* option_, double S0_, double r_, double sigma_)
    : option(option_), S0(S0_), r(r_), sigma(sigma_),
      nbPaths(0), meanPrice(0.0), M2(0.0), priceDefined(false)
{
    // Vérifier si l’option Asian pour CRR (selon cahier des charges)
    // Ici on permet Monte Carlo pour Asian
}

// Génération de nb_paths nouveaux chemins
void BlackScholesMCPricer::generate(int nb_new_paths) {
    std::vector<double> timeSteps;

    if(option->isAsianOption()) {
        AsianOption* asian = dynamic_cast<AsianOption*>(option);
        timeSteps = asian->getTimeSteps();
    } else {
        timeSteps.push_back(1.0); // European, temps final T = 1
    }

    for(int i=0; i<nb_new_paths; ++i){
        std::vector<double> path;
        double Sprev = S0;
        double t_prev = 0.0;

        for(double t : timeSteps){
            double dt = t - t_prev;
            double Z = MT::getInstance().rand_norm();
            double St = Sprev * std::exp((r - 0.5*sigma*sigma)*dt + sigma*std::sqrt(dt)*Z);
            path.push_back(St);
            Sprev = St;
            t_prev = t;
        }

        double payoffPath = option->payoffPath(path);
        nbPaths++;

        // Mise à jour moyenne et variance (Welford)
        double delta = payoffPath - meanPrice;
        meanPrice += delta / nbPaths;
        M2 += delta * (payoffPath - meanPrice);
    }

    priceDefined = true;
}

// Retourne le prix actuel actualisé
double BlackScholesMCPricer::operator()() const {
    if(!priceDefined) throw std::runtime_error("Price undefined");
    double T = option->isAsianOption() ? dynamic_cast<AsianOption*>(option)->getTimeSteps().back() : 1.0;
    return std::exp(-r*T) * meanPrice;
}

// Intervalle de confiance à 95%
std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
    if(!priceDefined) throw std::runtime_error("Price undefined");
    double T = option->isAsianOption() ? dynamic_cast<AsianOption*>(option)->getTimeSteps().back() : 1.0;

    double variance = (nbPaths > 1) ? M2/(nbPaths - 1) : 0.0;
    double SE = std::sqrt(variance / nbPaths);
    double discountedSE = SE * std::exp(-r*T);
    double discountedMean = meanPrice * std::exp(-r*T);

    return {discountedMean - 1.96*discountedSE, discountedMean + 1.96*discountedSE};
}
