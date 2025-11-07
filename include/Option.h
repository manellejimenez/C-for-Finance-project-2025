#pragma once
#include <vector>

class Option {
public:
    Option(double K);
    virtual ~Option() = default;

    virtual double payoff(double St) const = 0;

    virtual double payoffPath(const std::vector<double>& path) const {
        return payoff(path.back()); // European par défaut
    }

    virtual bool isAsianOption() const { return false; }

    double getStrike() const { return K; }

protected:
    double K;
};
