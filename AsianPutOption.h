#pragma once
#include "AsianOption.h"

class AsianPutOption : public AsianOption {

    public:

        // Constructor
        AsianPutOption(std::vector<double> timeSteps, double strike);

        // Destructor
        virtual ~AsianPutOption();

        //Methods
        OptionType GetOptionType() override;
        double payoff(double spotPrice) override;
};