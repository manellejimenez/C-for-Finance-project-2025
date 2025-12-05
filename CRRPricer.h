#pragma once
#include "Option.h"
#include "Binary_tree.h"

class CRRPricer {
private:
    int _depth;
    double _asset_price;
    double _up;
    double _down;
    double _interest_rate;
    Option* _option;
    
    BinaryTree<double> _tree;           // Pour stocker les prix
    BinaryTree<bool> _exercise_tree;    // Pour stocker (Partie 4)
    bool _computed;

    // Helper pour la formule factorielle
    double factorial(int n);

public:
    // Constructeur Partie 2 (Paramètres explicites)
    CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate);

    // Constructeur Partie 4 (Approximation Black-Scholes)
    CRRPricer(Option* option, int depth, double asset_price, double r, double volatility);

    void compute();
    
    double get(int n, int i);
    bool getExercise(int n, int i); // Spécifique Partie 4

    double operator()(bool closed_form = false);
};
