#include <iostream>
#include <vector>
#include "AsianOption.h"
#include "AsianCallOption.h"
#include "AsianPutOption.h"
#include "BlackScholesMCPricer.h"
#include "MT.h"

int main() {
    // Paramètres généraux
    double S0 = 100.0;    // prix initial du sous-jacent
    double r = 0.05;      // taux sans risque
    double sigma = 0.2;   // volatilité
    int N = 100000;       // nombre de chemins Monte Carlo
    double K = 100.0;     // strike
    std::vector<double> timeSteps = {0.25, 0.5, 0.75, 1.0}; // dates d'observation

    // --- Asian Call Option ---
    AsianCallOption call(timeSteps, K);
    BlackScholesMCPricer callPricer(&call, S0, r, sigma);
    callPricer.generate(N);

    std::cout << "Asian Call Option:" << std::endl;
    std::cout << "Prix estimé: " << callPricer() << std::endl;

    auto CI_call = callPricer.confidenceInterval();
    std::cout << "95% CI: [" << CI_call[0] << ", " << CI_call[1] << "]" << std::endl << std::endl;

    // --- Asian Put Option ---
    AsianPutOption put(timeSteps, K);
    BlackScholesMCPricer putPricer(&put, S0, r, sigma);
    putPricer.generate(N);

    std::cout << "Asian Put Option:" << std::endl;
    std::cout << "Prix estimé: " << putPricer() << std::endl;

    auto CI_put = putPricer.confidenceInterval();
    std::cout << "95% CI: [" << CI_put[0] << ", " << CI_put[1] << "]" << std::endl;

    return 0;

    std::cout << "Asian Put Option:" << std::endl;
std::cout << "Prix estimé: " << putPricer() << std::endl;

auto CI_put = putPricer.confidenceInterval();
std::cout << "95% CI: [" << CI_put[0] << ", " << CI_put[1] << "]" << std::endl;

}
