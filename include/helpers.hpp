
#ifndef NETSIM_PROJECT_HELPERS_HPP
#define NETSIM_PROJECT_HELPERS_HPP


#include <functional>
#include <random>

#include "types.hpp"

extern std::random_device rd;
extern std::mt19937 rng;

extern double default_probability_generator();

extern ProbabilityGenerator probability_generator;



#endif //NETSIM_PROJECT_HELPERS_HPP
