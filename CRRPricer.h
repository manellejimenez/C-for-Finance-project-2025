#pragma once

#include "Option.h"
#include "BinaryTree.h"

class CRRPricer {

    private:

        Option* _option;             
        int _depth;                   
        double _up, _down;            
        double _asset_price;         
        double _interest_rate; 

        BinaryTree<double> _tree;     
        BinaryTree<bool> _exerciseValidation; 


    public:

        // Constructeurs
        CRRPricer(Option* option, int depth, double up, double down, double asset_price, double interest_rate);
        CRRPricer(Option* option, int depth, double asset_price, double interest_rate, double volatility);

        // Destructeur
        virtual ~CRRPricer();

        //Methods
        void compute();                    
        double get(int n, int i);          
        bool getExercise(int i, int j);     
        double operator()(bool closed_form = false); 
        void display();     

        //Additionnal methods
        void validateParameters();
        double computeContinuationValue(int step, int i, double q);
        double computeStockPrice(int step, int i);
};