#pragma once
#include "AsianOption.h"

#pragma once
#include "AsianOption.h"
#include <algorithm> 

class AsianCallOption : public AsianOption {
public:
    // Constructor
    AsianCallOption(std::vector<double> timeSteps, double strike);

    // Destructor
    virtual ~AsianCallOption();

    
    OptionType GetOptionType() override;
    double payoff(double spotPrice) override;
};
