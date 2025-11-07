#pragma once
#include <random>

class MT {
public:
    static MT& getInstance() {
        static MT instance;
        return instance;
    }

    double rand_unif() { return uniform_dist(gen); }
    double rand_norm() { return normal_dist(gen); }

private:
    MT() : uniform_dist(0.0, 1.0), normal_dist(0.0,1.0) {}
    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<> uniform_dist;
    std::normal_distribution<> normal_dist;

    MT(MT const&) = delete;
    void operator=(MT const&) = delete;
};
