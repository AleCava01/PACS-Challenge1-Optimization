#ifndef VERBOSE_HPP
#define VERBOSE_HPP

#include <iostream>
#include <vector>
#include "parameters.hpp"

void print_vec(std::vector<double> x);

namespace verbose {
    void show_results(const std::vector<double>& x_opt, const Parameters& params) {
        std::cout << "-------------------------------------------------" << std::endl;
        std::cout << "OPTIMIZATION RESULTS " << std::endl;
        std::cout << "x = ";
        print_vec(x_opt);
        std::cout << "Minimum Function Value: " << params.func(x_opt) << std::endl;
        std::cout << "-------------------------------------------------" << std::endl;
    }
    void iterations_output(const unsigned k, const unsigned k_max){
        if(k<k_max){
        std::cout << "The method has converged in " << k << " iterations." << std::endl;
        }
        else{
            std::cout << "The maximum number of iterations (" << k_max << ") has been reached." << std::endl;
        }
    }
}

#include "functions.hpp"

#endif // VERBOSE_HPP