#include "MT.h"

std::mt19937 MT::_rng(std::random_device{}()); //randomize the seed, to make sure the random number is different each time

// Private constructor (empty since it's unused)
MT::MT() {}

// Method to generate a number in  Unif[0,1]
double MT::rand_unif() {
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(_rng);
}

// Method to generate a  number in N(0,1)
double MT::rand_norm() {
    static std::normal_distribution<double> dist(0.0, 1.0);
    return dist(_rng);
}