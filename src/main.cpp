#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <chrono>
#include <string>
#include "../include/parameters.hpp"
#include "../include/gradient_methods.hpp"
#include "../include/extra_methods.hpp"
#include "../include/verbose.hpp"
#include "../include/tests.hpp"



template <typename LRUpdateMethod>
void test_gradient_method(std::string test_name, Parameters test_params, LRUpdateMethod method);

int main() {

    // TESTING PARAMETERS
    Parameters test_params = test1(); // test1 and test2 are available

    // GRADIENT METHOD WITH DIFFERENT LEARNING RATE UPDATE METHODS

    verbose::print_header_result("test 1");

    // Inverse decay method
    test_gradient_method("Inverse Decay", test_params, lr_inv_decay);

    // Exponential decay method
    test_gradient_method("Exponential Decay", test_params, lr_exp_decay);

    // Constant Learning rate method
    test_gradient_method("Constant Rate", test_params, lr_constant);

    // APPROXIMATE LINE SEARCH - ARMIJO RULE
    test_gradient_method("Approx Line Search (Armijo)", test_params, lr_approx_line_search);

    // EXTRA METHODS

    size_t iter = 0; // iterations counter

    // HEAVY BALL METHOD
    double eta = 0.9;
    auto start_hb = std ::chrono::high_resolution_clock::now();
    std::vector<double> result_hb = heavy_ball(test_params, iter, eta);
    auto end_hb = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_hb= end_hb - start_hb;
    verbose::show_results("Heavy Ball", result_hb, test_params, elapsed_hb.count(), iter);


    // ADAM

    // the following parameters are set to the value suggested in
    // Kingma, D. P., & Ba, J. (2017). Adam: A method for stochastic optimization. arXiv preprint arXiv:1412.6980.
    // See README.md > Sources / Bibliography for more information
    double beta1 = 0.9, beta2 = 0.999, alpha_0 = 0.001, eps = 1e-8;

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<double> result = adam(test_params, iter, beta1, beta2, alpha_0, eps);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    verbose::show_results("ADAM", result, test_params, elapsed.count(), iter);

    verbose::dotted_separator();

    return 0;

}

template <typename LRUpdateMethod>
void test_gradient_method(std::string test_name, Parameters test_params, LRUpdateMethod method){
    size_t iter = 0; // iterations counter
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<double> result = eval(test_params, method, iter);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    verbose::show_results(test_name, result, test_params, elapsed.count(), iter);
}