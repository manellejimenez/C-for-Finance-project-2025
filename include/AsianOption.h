#pragma once
#include "Option.h"
#include <vector>
#include <numeric>

class AsianOption : public Option {
public:
    AsianOption(const std::vector<double>& timeSteps_, double K_);

    std::vector<double> getTimeSteps() const { return timeSteps; }

    double payoffPath(const std::vector<double>& path) const; // non-virtual

    bool isAsianOption() const override { return true; }

protected:
    std::vector<double> timeSteps;
};
