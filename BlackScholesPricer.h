#pragma once
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