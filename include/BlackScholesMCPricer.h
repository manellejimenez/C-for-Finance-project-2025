#pragma once
#include "Option.h"
#include "MT.h"
#include <vector>
#include <stdexcept>
#include <cmath>  // pour std::sqrt

class BlackScholesMCPricer {
public:
    BlackScholesMCPricer(Option* option_, double S0_, double r_, double sigma_);

    void generate(int nb_paths);
    double operator()() const;
    std::vector<double> confidenceInterval() const;
    int getNbPaths() const { return nbPaths; }

private:
    Option* option;
    double S0, r, sigma;
    int nbPaths;
    double meanPrice; // moyenne cumulée des payoffs
    double M2;        // pour calcul de variance (Welford)
    bool priceDefined;
};
