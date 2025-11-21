#pragma once
#include <iostream>
#include <string>
#include <cmath>
using namespace std;


class Option
{
private:
    double _expiry;
public:

    Option() : _expiry(0.0) {}

    double getExpiry() { return _expiry; }
    virtual double payoff(double) = 0;

    Option(double e)
    {
        _expiry = e;
        cout << "Une option à été créé" << endl;
    }

};



class EuropeanVanillaOption : public Option
{
private:
    double _strike;
    double _expiry;

public:

    EuropeanVanillaOption() : _strike(0.0), _expiry(0.0) {}

    EuropeanVanillaOption(double expiry, double strike) : Option(expiry), _strike(strike)
    {
        if (expiry < 0 || strike < 0)
        {
            throw std::invalid_argument("Expiry et strike doivent être non-négatifs");
        }
    }

    double getStrike() const { return _strike; }

    enum optionType { CALL, PUT };

    virtual optionType GetOptionType() = 0;

};




class CallOption : public EuropeanVanillaOption
{
public:
    CallOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {}

    double payoff(double z) const
    {
        return (z <= getStrike()) ? (z - getStrike()) : 0.0;
    }

    optionType GetOptionType() const
    {
        return CALL;
    }
};



class PutOption : public EuropeanVanillaOption
{
    PutOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {}

    double payoff(double z) const
    {
        return (z <= getStrike()) ? (getStrike() - z) : 0.0;
    }

    optionType GetOptionType() const
    {
        return PUT;
    }
};




class BlackScholesPricer : public EuropeanVanillaOption
{
private:
    EuropeanVanillaOption* _option;
    double _asset_price;
    double _interest_rate;
    double _volatility;

public:
    BlackScholesPricer(EuropeanVanillaOption* option, double asset_price, double interest_rate, double volatility) : _option(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility) {}



    double norm_cdf(double x)
    {
        return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
    }


    // Prix de l’option
    double operator()() {
        double T = _option->getExpiry();
        double K = _option->getStrike();

        double d1 = (std::log(_asset_price / K) + (_interest_rate + 0.5 * _volatility * _volatility) * T) / (_volatility * std::sqrt(T));
        double d2 = d1 - _volatility * std::sqrt(T);

        if (_option->GetOptionType() == EuropeanVanillaOption::CALL) {
            return _asset_price * norm_cdf(d1) - K * std::exp(-_interest_rate * T) * norm_cdf(d2);
        }
        else 
        { 
            return K * std::exp(-_interest_rate * T) * norm_cdf(-d2) - _asset_price * norm_cdf(-d1);
        }
    }

    
    double delta()
    {
        double T = _option->getExpiry();
        double K = _option->getStrike();

        double d1 = (std::log(_asset_price / K) + (_interest_rate + 0.5 * _volatility * _volatility) * T) / (_volatility * std::sqrt(T));

        if (_option->GetOptionType() == EuropeanVanillaOption::CALL)
        {
            return norm_cdf(d1);
        }
        else
        { // PUT
            return norm_cdf(d1) - 1;
        }
    }
};