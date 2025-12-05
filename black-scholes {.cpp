#pragma once
#include <cmath>
#include <stdexcept>
#include "Option.h"  // Ensure Option, EuropeanVanillaOption, etc. are included

// Abstract class for European Digital Options
class EuropeanDigitalOption : public Option {
private:
    double _strike;

public:
    enum optionType { call, put };

    EuropeanDigitalOption(double expiry, double strike)
        : Option(expiry), _strike(strike) {
        if (expiry < 0 || strike < 0)
            throw std::invalid_argument("Expiry and strike must be nonnegative.");
    }

    double getStrike() const { return _strike; }

    virtual double payo(double z) const = 0;
    virtual optionType GetOptionType() const = 0;

    friend class BlackScholesPricer;  // Optional if pricer needs access
};

// Digital Call Option
class EuropeanDigitalCallOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalCallOption(double expiry, double strike)
        : EuropeanDigitalOption(expiry, strike) {}

    double payo(double z) const override {
        return (z >= getStrike()) ? 1.0 : 0.0;
    }

    optionType GetOptionType() const override {
        return EuropeanDigitalOption::call;
    }
};

// Digital Put Option
class EuropeanDigitalPutOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalPutOption(double expiry, double strike)
        : EuropeanDigitalOption(expiry, strike) {}

    double payo(double z) const override {
        return (z <= getStrike()) ? 1.0 : 0.0;
    }

    optionType GetOptionType() const override {
        return EuropeanDigitalOption::put;
    }
};

// Black-Scholes Pricer capable of handling Digital Options
class BlackScholesPricer {
private:
    EuropeanDigitalOption* digitalOption;
    double S0, r, sigma;

    // Standard normal CDF
    double N(double x) const {
        return 0.5 * std::erfc(-x / std::sqrt(2));
    }

public:
    BlackScholesPricer(EuropeanDigitalOption* option_, double S0_, double r_, double sigma_)
        : digitalOption(option_), S0(S0_), r(r_), sigma(sigma_) {}

    double operator()() const {
        double K = digitalOption->getStrike();
        double T = digitalOption->getExpiry();
        double d1 = (std::log(S0 / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);

        if (digitalOption->GetOptionType() == EuropeanDigitalOption::call)
            return std::exp(-r * T) * N(d2);
        else
            return std::exp(-r * T) * N(-d2);
    }

    double delta() const {
        // Full formula for digital option Delta
        double K = digitalOption->getStrike();
        double T = digitalOption->getExpiry();
        double d1 = (std::log(S0 / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);
        double pdf_d2 = std::exp(-0.5 * d2 * d2) / std::sqrt(2 * M_PI);

        if (digitalOption->GetOptionType() == EuropeanDigitalOption::call)
            return pdf_d2 / (S0 * sigma * std::sqrt(T)) * std::exp(-r * T);
        else
            return -pdf_d2 / (S0 * sigma * std::sqrt(T)) * std::exp(-r * T);
    }
};
