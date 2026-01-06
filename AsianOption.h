#pragma once
#include "Option.h"
#include <vector>
#include <stdexcept>  

class AsianOption : public Option {

    protected :

        std::vector<double> _timeSteps;  
        double _strike;                  

    public :

        // Constructor
        AsianOption(std::vector<double> timeSteps, double strike);

        // Destructor
        virtual ~AsianOption();

        // Methods
        std::vector<double> getTimeSteps() override;
        double payoffPath(std::vector<double> spot_prices) override;
        double GetOptionStrike();
        bool isAsianOption() override;
};
