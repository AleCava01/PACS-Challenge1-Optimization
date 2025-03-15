#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include "functions.hpp"


int main(){

    // test parameters
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

    // Run gradient descent
    auto x_opt = eval(test_params);
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "Optimized result: ";
    print_vec(x_opt);
    std::cout << "Minimum Function Value: " << test_params.func(x_opt) << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;
    return 0;

}