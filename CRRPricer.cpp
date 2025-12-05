#include "CRRPricer.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

// Constructeur (Partie 2)
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate)
    : _option(option), _depth(depth), _asset_price(asset_price), 
      _up(up), _down(down), _interest_rate(interest_rate), _computed(false) {
    
    // Vérification arbitrage (Partie 2)
    if (_down <= -1 || _down >= _interest_rate || _interest_rate >= _up) {
        throw std::runtime_error("Arbitrage opportunity detected: D < R < U not satisfied.");
    }
}

// Constructeur approximation Black-Scholes (Partie 4)
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r, double volatility)
    : _option(option), _depth(depth), _asset_price(asset_price), _computed(false) {
    
    double h = option->getExpiry() / depth;
    double drift = r + (volatility * volatility) / 2.0;
    
    // Calcul de U, D et R selon le PDF
    _up = std::exp(drift * h + volatility * std::sqrt(h)) - 1.0;
    _down = std::exp(drift * h - volatility * std::sqrt(h)) - 1.0;
    _interest_rate = std::exp(r * h) - 1.0;
}

void CRRPricer::compute() {
    _tree.setDepth(_depth);
    _exercise_tree.setDepth(_depth);
    
    // Etape 1 : Initialisation à la maturité (Feuilles de l'arbre)
    for (int i = 0; i <= _depth; i++) {
        double spot = _asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, _depth - i);
        double val = _option->payoff(spot);
        
        _tree.setNode(_depth, i, val);
        _exercise_tree.setNode(_depth, i, val > 0); // On exerce si on gagne de l'argent
    }

    // Etape 2 : Induction arrière (Backward Induction)
    double q = (_interest_rate - _down) / (_up - _down);

    for (int n = _depth - 1; n >= 0; n--) {
        for (int i = 0; i <= n; i++) {
            
            // Calcul valeur de continuation
            double val_up = _tree.getNode(n + 1, i + 1);
            double val_down = _tree.getNode(n + 1, i);
            double continuation_value = (q * val_up + (1 - q) * val_down) / (1 + _interest_rate);

            // Partie 4 : Logique Option Américaine
            if (_option->isAmericanOption()) {
                double current_spot = _asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, n - i);
                double intrinsic_value = _option->payoff(current_spot);

                if (intrinsic_value >= continuation_value) {
                    _tree.setNode(n, i, intrinsic_value);
                    _exercise_tree.setNode(n, i, true); // TRUE : Exercice anticipé optimal
                } else {
                    _tree.setNode(n, i, continuation_value);
                    _exercise_tree.setNode(n, i, false); // FALSE : On garde l'option
                }
            } 
            // Partie 2 : Logique Option Européenne standard
            else {
                _tree.setNode(n, i, continuation_value);
                _exercise_tree.setNode(n, i, false);
            }
        }
    }
    _computed = true;
}

double CRRPricer::get(int n, int i) {
    if (!_computed) compute();
    return _tree.getNode(n, i);
}

bool CRRPricer::getExercise(int n, int i) {
    if (!_computed) compute();
    return _exercise_tree.getNode(n, i);
}

double CRRPricer::factorial(int n) {
    double res = 1.0;
    for (int i = 2; i <= n; i++) res *= i;
    return res;
}

double CRRPricer::operator()(bool closed_form) {
    if (closed_form) {
        // Formule fermée (Partie 2) - Interdit pour les américaines
        if (_option->isAmericanOption()) {
             // Fallback sur la méthode d'arbre si l'utilisateur se trompe
             if (!_computed) compute();
             return _tree.getNode(0, 0);
        }

        double N = _depth;
        double q = (_interest_rate - _down) / (_up - _down);
        double sum = 0.0;

        for (int i = 0; i <= N; i++) {
            double nCr = factorial(N) / (factorial(i) * factorial(N - i));
            
            double spot = _asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, N - i);
            double probability = nCr * std::pow(q, i) * std::pow(1 - q, N - i);
            
            sum += probability * _option->payoff(spot);
        }
        
        return (1.0 / std::pow(1 + _interest_rate, N)) * sum;
    } 
    else {
        // Calcul par arbre (Partie 2 & 4)
        if (!_computed) compute();
        return _tree.getNode(0, 0);
    }
}
