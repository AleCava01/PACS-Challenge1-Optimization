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
        return 2 * x[0] * x[1] + 4 * std::pow(x[0], 4) + 2 * std::pow(x[1], 2) + 2 * x[0];
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
    test_params.sigma = 0.1;
    return test_params;
}

Parameters test2() {
    Parameters test_params;
    test_params.n = 2;
    test_params.func = [](const std::vector<double>& x) {
        
        return std::pow(x[0], 2) + std::pow(x[1], 2) + 2 * x[0] * x[1];
    };
    test_params.grad_func = [](const std::vector<double>& x) -> std::vector<double> {
        return {
            2 * x[0] + 2 * x[1], 
            2 * x[1] + 2 * x[0] 
        };
    };
    test_params.eps_r = 1e-6; 
    test_params.eps_s = 1e-6;
    test_params.alpha_zero = 0.1;
    test_params.x0 = {1.0, 1.0};
    test_params.k_max = 50;  
    test_params.mu = 1e-4; 
    test_params.sigma = 0.4;  
    return test_params;
}

Parameters test3() {
    Parameters test_params;
    test_params.n = 6; 
    test_params.func = [](const std::vector<double>& x) {
        return std::pow(x[0], 2) + 2 * std::pow(x[1], 2) + 3 * std::pow(x[2], 2) + 4 * std::pow(x[3], 3) 
               + std::sin(x[4]) + std::exp(-std::pow(x[5], 2));
    };
    test_params.grad_func = [](const std::vector<double>& x) -> std::vector<double> {
        return {
            2 * x[0],                       
            4 * x[1],                      
            6 * x[2],        
            12 * std::pow(x[3], 2), 
            std::cos(x[4]),      
            -2 * x[5] * std::exp(-std::pow(x[5], 2))
        };
    };
    test_params.eps_r = 1e-6; 
    test_params.eps_s = 1e-6; 
    test_params.alpha_zero = 0.1;
    test_params.x0 = {1.0, -1.0, 0.5, 0.2, 0.3, -0.1};
    test_params.k_max = 1000000; 
    test_params.mu = 1e-3;
    test_params.sigma = 0.3;
    return test_params;
}

#endif // TESTS_HPP
