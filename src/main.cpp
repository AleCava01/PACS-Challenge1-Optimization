#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include<chrono>
#include "../include/parameters.hpp"
#include "../include/functions.hpp"
#include "../include/verbose.hpp"
#include "../include/tests.hpp"

int main() {

    Parameters test_params = test1(); // test1 and test2 are available

    verbose::print_header_result();

    // INV DECAY
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<double> x_opt_inv_decay = eval(test_params, lr_inv_decay);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_inv_decay = end - start;
    verbose::show_results("Inverse Decay", x_opt_inv_decay, test_params, elapsed_inv_decay.count());

    // EXP DECAY
    start = std::chrono::high_resolution_clock::now();
    std::vector<double> x_opt_exp_decay = eval(test_params, lr_exp_decay);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_exp_decay = end - start;
    verbose::show_results("Exponential Decay", x_opt_exp_decay, test_params, elapsed_exp_decay.count());

    // CONSTANT LEARNING RATE
    start = std::chrono::high_resolution_clock::now();
    std::vector<double> x_opt_constant = eval(test_params, lr_constant);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_constant = end - start;
    verbose::show_results("Constant Rate", x_opt_constant, test_params, elapsed_constant.count());

    // APPROXIMATE LINE SEARCH - ARMIJO RULE
    start = std::chrono::high_resolution_clock::now();
    std::vector<double> x_opt_approx_ls = eval(test_params, lr_approx_line_search);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_approx_ls = end - start;
    verbose::show_results("Approx Line Search", x_opt_approx_ls, test_params, elapsed_approx_ls.count());

    return 0;
}
