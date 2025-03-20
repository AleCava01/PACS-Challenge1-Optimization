#ifndef EXTRA_METHODS_HPP
#define EXTRA_METHODS_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "parameters.hpp"
#include "utils.hpp"


// --- EXTRA METHODS ---------------------------------------------------------------

// Heavy Ball
std::vector<double> heavy_ball(const Parameters& params, size_t& k,const double eta);

// ADAM
std::vector<double> adam(const Parameters& params, size_t& k, const double beta1, const double beta2, double alpha,const double eps);
#endif // EXTRA_METHODS_HPP