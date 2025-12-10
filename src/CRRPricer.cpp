#include "CRRPricer.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

// Constructeur Partie 2
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate)
    // ORDRE MODIFIÉ POUR CORRESPONDRE AU HEADER ET SUPPRIMER LES WARNINGS
    : _depth(depth), _asset_price(asset_price), _option(option),
      _up(up), _down(down), _interest_rate(interest_rate), _computed(false) {

    if (_down <= -1 || _down >= _interest_rate || _interest_rate >= _up) {
        throw std::runtime_error("Arbitrage opportunity: Check parameters D < R < U");
    }
}

// Constructeur Partie 4
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r, double volatility)
    // ORDRE MODIFIÉ ICI AUSSI
    : _depth(depth), _asset_price(asset_price), _option(option), _computed(false) {

    double h = option->getExpiry() / depth;
    double drift = r + (volatility * volatility) / 2.0;

    _up = std::exp(drift * h + volatility * std::sqrt(h)) - 1.0;
    _down = std::exp(drift * h - volatility * std::sqrt(h)) - 1.0;
    _interest_rate = std::exp(r * h) - 1.0;
}

void CRRPricer::compute() {
    // Si votre classe d'arbre s'appelle 'TriangleTree' ou 'BinaryTree', assurez-vous que le nom est bon
    _tree.setDepth(_depth);
    _exercise_tree.setDepth(_depth);

    // 1. Initialisation des feuilles (à maturité N)
    for (int i = 0; i <= _depth; i++) {
        // S(N, i) = S0 * (1+U)^i * (1+D)^(N-i)
        double spot = _asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, _depth - i);
        double val = _option->payoff(spot);

        _tree.setNode(_depth, i, val);
        // À la fin, on exerce si on gagne de l'argent
        _exercise_tree.setNode(_depth, i, val > 0);
    }

    // 2. Backward Induction (On remonte l'arbre)
    double q = (_interest_rate - _down) / (_up - _down);

    for (int n = _depth - 1; n >= 0; n--) {
        for (int i = 0; i <= n; i++) {

            // Valeur de continuation (si on garde l'option)
            double val_up = _tree.getNode(n + 1, i + 1);
            double val_down = _tree.getNode(n + 1, i);

            // Actualisation
            double continuation_value = (q * val_up + (1 - q) * val_down) / (1 + _interest_rate);

            // Gestion Américaine vs Européenne
            if (_option->isAmericanOption()) {
                // Valeur intrinsèque (si on exerce maintenant)
                // Recalcul du spot à cette date et ce noeud
                double current_spot = _asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, n - i);
                double intrinsic_value = _option->payoff(current_spot);

                if (intrinsic_value >= continuation_value) {
                    _tree.setNode(n, i, intrinsic_value);
                    _exercise_tree.setNode(n, i, true); // TRUE: on exerce
                } else {
                    _tree.setNode(n, i, continuation_value);
                    _exercise_tree.setNode(n, i, false); // FALSE: on attend
                }
            } else {
                // Cas Européen simple
                _tree.setNode(n, i, continuation_value);
                _exercise_tree.setNode(n, i, false); // Pas d'exercice anticipé possible
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
    // Attention : double a une précision limitée pour les grands factoriels
    // Pour n > 170, cela renverra "inf", mais pour un depth raisonnable (ex: 100), ça peut passer.
    double res = 1.0;
    for (int i = 2; i <= n; i++) res *= i;
    return res;
}

double CRRPricer::operator()(bool closed_form) {
    if (closed_form) {
        // Formule fermée (Partie 2, Page 7) - Seulement pour Européennes
        if (_option->isAmericanOption()) {
             // Protection : Impossible d'utiliser la formule fermée pour les américaines
             if (!_computed) compute();
             return _tree.getNode(0, 0);
        }

        double N = _depth;
        double q = (_interest_rate - _down) / (_up - _down);
        double sum = 0.0;

        for (int i = 0; i <= N; i++) {
            // Calcul combinaison nCr = N! / (i! * (N-i)!)
            double nCr = factorial(N) / (factorial(i) * factorial(N - i));

            double spot = _asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, N - i);
            double probability = nCr * std::pow(q, i) * std::pow(1 - q, N - i);

            sum += probability * _option->payoff(spot);
        }

        return (1.0 / std::pow(1 + _interest_rate, N)) * sum;
    }
    else {
        // Méthode par arbre (Partie 2 et 4)
        if (!_computed) compute();
        return _tree.getNode(0, 0);
    }
}

