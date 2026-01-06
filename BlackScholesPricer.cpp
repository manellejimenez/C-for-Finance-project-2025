#include "BlackScholesPricer.h"
//#include "EuropeanVanillaOption.h"
#include "Option.h"

#include <cmath>
const double pi = 3.14159265358979323846;

// Constructeur de la classe
BlackScholesPricer::BlackScholesPricer(Option* option, double asset_price, double interest_rate, double volatility) :
    _option(option),_asset_price(asset_price),_interest_rate(interest_rate), _volatility(volatility)
{
    _option = option;
    _asset_price = asset_price;
    _interest_rate = interest_rate;
    _volatility = volatility;
}

// Destructeur virtuel
BlackScholesPricer::~BlackScholesPricer() {}

// Fonction pour la distribution normale
double BlackScholesPricer::NormalDistr(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2));
}

// Calcul du prix de l'option
double BlackScholesPricer::operator()() {
    double Strike = _option->GetOptionStrike();
    double Expiry = _option->getExpiry();

    double d1 = (std::log(_asset_price / Strike) + (_interest_rate + 0.5 * _volatility * _volatility) * Expiry)
        / (_volatility * std::sqrt(Expiry));
    double d2 = d1 - _volatility * std::sqrt(Expiry);

    if (_option->GetOptionType() == OptionType::call) {
        if (_option->isDigital()) {
            return std::exp(-Expiry * _interest_rate) * NormalDistr(d2);
        }
        return _asset_price * NormalDistr(d1) - Strike * std::exp(-Expiry * _interest_rate) * NormalDistr(d2);
    }
    else {
        if (_option->isDigital()) {
            return std::exp(-Expiry * _interest_rate)* NormalDistr(-d2);
        }
        return -_asset_price * NormalDistr(-d1) + Strike * std::exp(-Expiry * _interest_rate) * NormalDistr(-d2);
    }
}

// Fonction pour la densite normale
double BlackScholesPricer::NormalDensity(double var) {
    return 1 / std::sqrt(2 * pi) * std::exp(-0.5 * var * var);
}

// Calcul de Delta for Digital & Vanilla options
double BlackScholesPricer::delta() {
    double Strike = _option->GetOptionStrike();
    double Expiry = _option->getExpiry();

    double d1 = (std::log(_asset_price / Strike) + (_interest_rate + 0.5 * _volatility * _volatility) * Expiry) / (_volatility * std::sqrt(Expiry));
    double d2 = d1 - _volatility * std::sqrt(Expiry);

    if (_option->GetOptionType() == OptionType::call) {
        if (_option->isDigital()) {
            return std::exp(-_interest_rate * _option->GetOptionStrike()) * NormalDensity(d2) 
                / std::sqrt(_option->getExpiry()) * _asset_price * _volatility;
        }
        return NormalDistr(d1);
    }
    else {
        if (_option->isDigital()) {
            return std::exp(-_interest_rate * _option->GetOptionStrike()) * -NormalDensity(-d2)
                / std::sqrt(_option->getExpiry()) * _asset_price * _volatility;
        }
        return NormalDistr(d1) - 1;
    }
}
