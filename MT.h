#pragma once
#include <random>

class MT {
private:
    MT();
    static std::mt19937 _rng;

public:
    MT(const MT&) = delete;
    MT& operator=(const MT&) = delete;

    // Static methods to generate random numbers
    static double rand_unif(); //Unif[0,1]
    static double rand_norm(); //N(0,1)
};