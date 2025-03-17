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
    test_params.k_max = 10000;
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

Parameters test3() {
    Parameters test_params;
    test_params.n = 6;  // La dimensione dell'input è 6
    test_params.func = [](const std::vector<double>& x) {
        // La funzione obiettivo f(x) = x0^2 + 2*x1^2 + 3*x2^2 + 4*x3^3 + sin(x4) + e^(-x5^2)
        return std::pow(x[0], 2) + 2 * std::pow(x[1], 2) + 3 * std::pow(x[2], 2) + 4 * std::pow(x[3], 3) 
               + std::sin(x[4]) + std::exp(-std::pow(x[5], 2));
    };
    test_params.grad_func = [](const std::vector<double>& x) -> std::vector<double> {
        // Il gradiente della funzione obiettivo (derivate parziali)
        return {
            2 * x[0],                             // df/dx0 = 2*x0
            4 * x[1],                             // df/dx1 = 4*x1
            6 * x[2],                             // df/dx2 = 6*x2
            12 * std::pow(x[3], 2),               // df/dx3 = 12*x3^2
            std::cos(x[4]),                       // df/dx4 = cos(x4)
            -2 * x[5] * std::exp(-std::pow(x[5], 2)) // df/dx5 = -2*x5*exp(-x5^2)
        };
    };
    test_params.eps_r = 1e-6;  // Tolleranza per la convergenza relativa
    test_params.eps_s = 1e-6;  // Tolleranza per il passo
    test_params.alpha_zero = 0.1; // Passo iniziale per l'ottimizzazione
    test_params.x0 = {1.0, -1.0, 0.5, 0.2, 0.3, -0.1}; // Parametri iniziali
    test_params.k_max = 1000000;  // Numero massimo di iterazioni
    test_params.mu = 1e-3;  // Parametro per la ricerca lineare
    test_params.sigma = 0.3;  // Parametro per la ricerca lineare
    return test_params;
}

#endif // TESTS_HPP
