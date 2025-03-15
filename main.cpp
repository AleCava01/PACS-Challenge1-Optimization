#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include "functions.hpp"
#include "verbose.hpp"


int main(){

    // Define testing parameters
    parameters test_params;
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

    // Run gradient descent
    std::vector<double> x_opt = eval(test_params, lr_exp_decay);

    // Show results
    verbose::show_results(x_opt, test_params);

}