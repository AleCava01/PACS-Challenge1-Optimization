#ifndef TESTS_HPP
#define TESTS_HPP

#include <vector>
#include <cmath>
#include <functional>
#include "parameters.hpp"

Parameters test1(){
    Parameters test_params;
    test_params.n = 2;
    test_params.func = [](const std::vector<double>& x) {
        return 2 * x[0] * x[1] + 4 * std::pow(x[0], 4) + std::pow(2 * x[1], 2) + 2 * x[0];
    };
    test_params.grad_func = [](const std::vector<double>& x) -> std::vector<double> {
        return {
            2 * x[1] + 16 * std::pow(x[0], 3) + 2,
            2 * x[0] + 4 * x[1]
        };
    };
    test_params.eps_r = 1e-6;  
    test_params.eps_s = 1e-6;
    test_params.alpha_zero = 0.1; // set to 0.1 instead of 1. The method appears to be highly sensitive to this parameter.
    test_params.x0 = {0.0, 0.0};
    test_params.k_max = 100;
    test_params.mu = 1e-3;
    test_params.sigma = 0.3;
    return test_params;
}

Parameters test2() {
    Parameters test_params;
    test_params.n = 2;
    test_params.func = [](const std::vector<double>& x) {
        // A new function for test2 (a different function for testing)
        return std::pow(x[0], 2) + std::pow(x[1], 2) + 2 * x[0] * x[1];
    };
    test_params.grad_func = [](const std::vector<double>& x) -> std::vector<double> {
        // Gradient of the new function
        return {
            2 * x[0] + 2 * x[1],  // Gradient with respect to x0
            2 * x[1] + 2 * x[0]   // Gradient with respect to x1
        };
    };
    test_params.eps_r = 1e-6;  // Residual tolerance
    test_params.eps_s = 1e-6;  // Step tolerance
    test_params.alpha_zero = 0.1; // Set to a different starting value for alpha
    test_params.x0 = {1.0, 1.0}; // Different starting point
    test_params.k_max = 50;     // Reduce max iterations for this test
    test_params.mu = 1e-4;     // Different learning rate decay factor
    test_params.sigma = 0.4;   // Slightly different sigma for Armijo condition
    return test_params;
}

#endif // TESTS_HPP
