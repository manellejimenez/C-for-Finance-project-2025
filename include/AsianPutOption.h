#pragma once
#include "AsianOption.h"
#include <algorithm>

class AsianPutOption : public AsianOption {
public:
    AsianPutOption(const std::vector<double>& timeSteps_, double K_)
        : AsianOption(timeSteps_, K_) {}

    double payoff(double St) const override {
        return std::max(K - St, 0.0);
    }
};
