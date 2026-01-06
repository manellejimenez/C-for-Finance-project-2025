#pragma once
#include "Option.h"
#include "MT.h"
#include <vector>
#include <stdexcept>

class BlackScholesMCPricer {

    private:

        Option* _option;
        double _initialPrice;
        double _interestRate;
        double _volatility;
        int _nbPaths;
        double _sumPayoffs;
        double _sumPayoffsSquared;


    public:

        // Constructor
        BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility);

        // Destructor
        virtual ~BlackScholesMCPricer();

        // Methods
        int getNbPaths() const;
        void generate(int nb_paths);
        double operator()() const;
        std::vector<double> confidenceInterval() const;
};