#include <iostream>
#include "Option.h"
#include "EuropeanVanillaOption.h"
#include "CallOption.h"
#include "PutOption.h"
#include "BlackScholesPricer.h"

int main()
{
    std::cout << "===== TEST DES CONSTRUCTEURS =====" << std::endl;

    try {
        CallOption call(1.0, 100.0);
        PutOption put(1.0, 100.0);

        std::cout << "Constructeurs OK" << std::endl;

        std::cout << "\n===== TEST DES GETTERS =====" << std::endl;
        std::cout << "Call expiry = " << call.getExpiry() << std::endl;
        std::cout << "Call strike = " << call.getStrike() << std::endl;

        std::cout << "Put expiry = " << put.getExpiry() << std::endl;
        std::cout << "Put strike = " << put.getStrike() << std::endl;

        std::cout << "\n===== TEST PAYOFF =====" << std::endl;
        std::cout << "Call payoff (S=120) = " << call.payoff(120.0) << " (attendu : 20)" << std::endl;
        std::cout << "Call payoff (S=80)  = " << call.payoff(80.0)  << " (attendu : 0)" << std::endl;

        std::cout << "Put payoff (S=80)   = " << put.payoff(80.0)  << " (attendu : 20)" << std::endl;
        std::cout << "Put payoff (S=120)  = " << put.payoff(120.0) << " (attendu : 0)" << std::endl;

        std::cout << "\n===== TEST BLACK-SCHOLES =====" << std::endl;

        double S = 105.0;
        double r = 0.05;
        double sigma = 0.2;

        BlackScholesPricer pricerCall(&call, S, r, sigma);
        BlackScholesPricer pricerPut(&put,   S, r, sigma);

        std::cout << "Prix Call BS = " << pricerCall.price() << std::endl;
        std::cout << "Delta Call   = " << pricerCall.delta() << std::endl;

        std::cout << "Prix Put BS  = " << pricerPut.price() << std::endl;
        std::cout << "Delta Put    = " << pricerPut.delta() << std::endl;

    }
    catch (const std::exception& e)
    {
        std::cerr << "ERREUR : " << e.what() << std::endl;
    }

    std::cout << "\n===== FIN DES TESTS =====" << std::endl;
    return 0;
}
