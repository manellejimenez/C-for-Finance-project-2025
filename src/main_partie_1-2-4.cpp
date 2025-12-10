#include <iostream>
#include <iomanip> // Pour afficher les chiffres après la virgule
#include <cmath>
#include "EuropeanDigitalOption.h"
#include "AmericanOption.h"
#include "EuropeanVanillaOption.h"
#include "CallOption.h"
#include "PutOption.h"
#include "CRRPricer.h"
#include "BlackScholesPricer.h"

int main() {
    //Paramètres
    double S0 = 100.0;   // Stock Price
    double K  = 101.0;   // Strike
    double T  = 5.0;     // Maturité
    int    N  = 5;       // Profondeur (Steps)

    // Paramètres explicites "CRR Params"
    double U = 0.05;
    double D = -0.045;
    double R = 0.01;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "=== TEST ===" << std::endl;
    std::cout << "Parametres: S0=" << S0 << ", K=" << K << ", N=" << N
              << ", U=" << U << ", D=" << D << ", R=" << R << std::endl << std::endl;

    //Test European Digital Call
    EuropeanDigitalCallOption digCall(T, K);
    CRRPricer pricerDigCall(&digCall, N, S0, U, D, R);
    double resDigCall = pricerDigCall();

    std::cout << "[European Digital Call]" << std::endl;
    std::cout << "Resultat Code : " << resDigCall << std::endl;
    std::cout << "--------------------------------"<< std::endl;

    // Digital Put
    EuropeanDigitalPutOption digPut(T, K);
    CRRPricer pricerDigPut(&digPut, N, S0, U, D, R);
    double resDigPut = pricerDigPut();

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "[European Digital Put]" << std::endl;
    std::cout << "Resultat Code : " << resDigPut << std::endl;

    //TEST 3 : American Call
    AmericanCallOption amCall(T, K);
    CRRPricer pricerAmCall(&amCall, N, S0, U, D, R);
    double resAmCall = pricerAmCall();

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "[American Call]" << std::endl;
    std::cout << "Resultat Code : " << resAmCall << std::endl;

    // TEST 4 : American Put
    AmericanPutOption amPut(T, K);
    CRRPricer pricerAmPut(&amPut, N, S0, U, D, R);
    double resAmPut = pricerAmPut();

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "[American Put]" << std::endl;
    std::cout << "Resultat Code : " << resAmPut << std::endl;

    //TEST 1 : European Call
    CallOption euroCall(T, K);
    CRRPricer pricerEuroCall(&euroCall, N, S0, U, D, R);
    double resEuroCall = pricerEuroCall();

    std::cout << "[European Call]" << std::endl;
    std::cout << "Resultat Code : " << resEuroCall << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    //TEST 2 : European Put
    PutOption euroPut(T, K);
    CRRPricer pricerEuroPut(&euroPut, N, S0, U, D, R);
    double resEuroPut = pricerEuroPut();

    std::cout << "[European Put]" << std::endl;
    std::cout << "Resultat Code : " << resEuroPut << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    // Paramètres
    double S_BS = 100.0;
    double K_BS = 101.0;
    double T_BS = 1.0;
    double r_BS = 0.05;

    double sigma_BS = std::sqrt(0.05);

    std::cout << "Parametres BS: S=" << S_BS << ", K=" << K_BS << ", T=" << T_BS
              << ", r=" << r_BS << ", sigma=" << sigma_BS << std::endl << std::endl;

    //Test Call Vanilla Black-Scholes
    CallOption bsCall(T_BS, K_BS);
    BlackScholesPricer pricerBSCall(&bsCall, S_BS, r_BS, sigma_BS);

    std::cout << "[Black-Scholes Call]" << std::endl;
    std::cout << "Prix  : " << pricerBSCall() << std::endl;
    std::cout << "Delta : " << pricerBSCall.delta() << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    //Test Put Vanilla Black-Scholes
    PutOption bsPut(T_BS, K_BS);
    BlackScholesPricer pricerBSPut(&bsPut, S_BS, r_BS, sigma_BS);

    std::cout << "[Black-Scholes Put]" << std::endl;
    std::cout << "Prix  : " << pricerBSPut() << std::endl;
    std::cout << "Delta : " << pricerBSPut.delta() << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    //Test Digital Call Black-Scholes
    EuropeanDigitalCallOption bsDigCall(T_BS, K_BS);
    BlackScholesPricer pricerBSDigCall(&bsDigCall, S_BS, r_BS, sigma_BS);

    std::cout << "[Black-Scholes Digital Call]" << std::endl;
    std::cout << "Prix  : " << pricerBSDigCall() << std::endl;
    std::cout << "Delta : " << pricerBSDigCall.delta() << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    //Test Digital Put Black-Scholes
    EuropeanDigitalPutOption bsDigPut(T_BS, K_BS);
    BlackScholesPricer pricerBSDigPut(&bsDigPut, S_BS, r_BS, sigma_BS);

    std::cout << "[Black-Scholes Digital Put]" << std::endl;
    std::cout << "Prix  : " << pricerBSDigPut() << std::endl;
    std::cout << "Delta : " << pricerBSDigPut.delta() << std::endl;
    return 0;
}
