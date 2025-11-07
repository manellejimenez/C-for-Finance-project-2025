#pragma once
#include "AsianOption.h"
#include <algorithm>

class AsianCallOption : public AsianOption {
public:
    AsianCallOption(const std::vector<double>& timeSteps_, double K_)
        : AsianOption(timeSteps_, K_) {}

    double payoff(double St) const override {
        return std::max(St - K, 0.0);
    }
};
