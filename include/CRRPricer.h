#pragma once
#include "Option.h"
#include "BinaryTree.h"

class CRRPricer {
private:
    int _depth;
    double _asset_price;
    double _up;
    double _down;
    double _interest_rate;
    Option* _option;

    BinaryTree<double> _tree;           // Arbre des prix
    BinaryTree<bool> _exercise_tree;    // Arbre d'exercice (Partie 4)
    bool _computed;

    // Méthode utilitaire pour la factorielle
    double factorial(int n);

public:
    // Constructeur Partie 2 (Paramètres CRR explicites)
    CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate);

    // Constructeur Partie 4 (Approximation Black-Scholes)
    CRRPricer(Option* option, int depth, double asset_price, double r, double volatility);

    void compute();

    // Accesseurs demandés
    double get(int n, int i);
    bool getExercise(int n, int i);

    // Opérateur de pricing (avec option formule fermée)
    double operator()(bool closed_form = false);
};

