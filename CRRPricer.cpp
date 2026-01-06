#include "CRRPricer.h"
#include <stdexcept>
#include <cmath>
#include <algorithm>

//Constructeur
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate)
    : _option(option), _depth(depth), _asset_price(asset_price), _up(up), _down(down), _interest_rate(interest_rate) {
    validateParameters();
}

//Pour verifier si les parametres sont coherents 
void CRRPricer::validateParameters() {
    if (_down < -1 || _down > _up || _interest_rate <= -1 || _interest_rate > _up) {
        throw std::runtime_error("Arbitrage opportunity detected.");
    }
    if (_asset_price <= 0) {
        throw std::runtime_error("Invalid parameters: asset price must be positive.");
    }
    if (_option->isAsianOption()) {
        throw std::invalid_argument("Asian Option not supported.");
    }
    if (_option->isAmericanOption()) {
        _exerciseValidation.setDepth(_depth);
    }
}


double CRRPricer::computeContinuationValue(int step, int i, double q) {

    return (q * _tree.getNode(step + 1, i + 1) +
        (1 - q) * _tree.getNode(step + 1, i)) / (1 + _interest_rate);
}

double CRRPricer::computeStockPrice(int step, int i) {
    return _asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, step - i);
}


// Constructeur TD08
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double interest_rate, double volatility)
    : _option(option), _depth(depth), _asset_price(asset_price) {

    double h = _option->getExpiry() / _depth;

    _up = std::exp((interest_rate + std::pow(volatility, 2) / 2) 
        * h + volatility * std::sqrt(h)) - 1;

    _down = std::exp((interest_rate + std::pow(volatility, 2) / 2)
        * h - volatility * std::sqrt(h)) - 1;

    _interest_rate = std::exp(interest_rate * h) - 1;

    validateParameters();
}

//Compute
void CRRPricer::compute() {
    
    _tree.setDepth(_depth);
    double q = (_interest_rate - _down) / (_up - _down);

    for (int i = 0; i <= _depth; i++) {
        double stock_price = computeStockPrice(_depth, i);
        _tree.setNode(_depth, i, _option->payoff(stock_price));
    }
  
    for (int step = _depth - 1; step >= 0; --step) {

        for (int i = 0; i <= step; ++i) {

            double stock_price = computeStockPrice(step, i);
            double continuationValue = computeContinuationValue(step, i, q);

            if (_option->isAmericanOption()) {

                double intrinsicValue = _option->payoff(stock_price);
                _tree.setNode(step, i, std::max(continuationValue, intrinsicValue));
                _exerciseValidation.setNode(step, i, intrinsicValue > continuationValue);
            }
            else {

                _tree.setNode(step, i, continuationValue);
            }
        }
    }
}


//Calcul du prix
double CRRPricer::operator()(bool closed_form) {

    if (closed_form) {
        double q = (_interest_rate - _down) / (_up - _down);
        double value = 0;

        for (int i = 0; i <= _depth; i++) {

            double stock_price = computeStockPrice(_depth, i);
            value += std::tgamma(_depth + 1) * std::pow(q, i) * std::pow(1 - q, _depth - i) *
                _option->payoff(stock_price) / (std::tgamma(i + 1) * std::tgamma(_depth - i + 1));
        }

        return value / std::pow(1 + _interest_rate, _depth);
    }
    else {

        return get(0, 0);
    }
}

//On recupere la valeur d'un node
double CRRPricer::get(int n, int i) {
    compute();
    return _tree.getNode(n, i);
}

//Pareil pour le fait d'exercer ou non 
bool CRRPricer::getExercise(int i, int j) {
    compute();
    return _exerciseValidation.getNode(i, j);
}

//Destructeur
CRRPricer::~CRRPricer() {};

//Affichage de l'arbre en appelant la methode display
void CRRPricer::display() {
    _tree.display();
}