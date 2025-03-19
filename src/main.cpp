#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <chrono>
#include <string>
#include "../include/parameters.hpp"
#include "../include/functions.hpp"
#include "../include/verbose.hpp"
#include "../include/tests.hpp"

template <typename LRUpdateMethod>
void test_method(std::string test_name, Parameters test_params, LRUpdateMethod method);

int main() {

    // TESTING PARAMETERS
    Parameters test_params = test1(); // test1 and test2 are available

    // EVAL FUNCTION WITH DIFFERENT METHODS

    verbose::print_header_result();

    // Inverse decay method
    test_method("Inverse Decay", test_params, lr_inv_decay);

    // Exponential decay method
    test_method("Exponential Decay", test_params, lr_exp_decay);

    // Constant Learning rate method
    test_method("Constant Rate", test_params, lr_constant);

    // APPROXIMATE LINE SEARCH - ARMIJO RULE
    test_method("Approx Line Search (Armijo)", test_params, lr_approx_line_search);


    // ADAM
    double beta1 = 0.9; // suggested test value
    double beta2 = 0.999;
    double alpha_0 = 0.001;
    size_t iter = 0; // iterations counter

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<double> result = adam(test_params, iter, beta1, beta2,alpha_0);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    verbose::show_results("ADAM", result, test_params, elapsed.count(), iter);


    verbose::dotted_separator();
    
    return 0;
}


template <typename LRUpdateMethod>
void test_method(std::string test_name, Parameters test_params, LRUpdateMethod method){
    size_t iter = 0; // iterations counter
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<double> result = eval(test_params, method, iter);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    verbose::show_results(test_name, result, test_params, elapsed.count(), iter);
}