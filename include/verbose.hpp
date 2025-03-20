#ifndef VERBOSE_HPP
#define VERBOSE_HPP

#include <iostream>
#include <vector>
#include <iomanip>
#include "parameters.hpp"

void print_vec(const std::vector<double>& x);
double norm2(const std::vector<double>& vec);
std::string vectorToString(const std::vector<double>& vec);

namespace verbose {
    void dotted_separator(){
        std::cout << "***************************************************************************************************************************" << std::endl;
    }
    void print_header_result(const std::string& testname){
        dotted_separator();
        std::cout << "OPTIMIZATION RESULTS - " << testname << std::endl;
        dotted_separator();
        // Print the headers with fixed width for neat columns
        std::cout << std::setw(35) << std::left << "Method"
                  << std::setw(15) << std::left << "min value"
                  << std::setw(15) << std::left << "residual"
                  << std::setw(15) << std::left << "time" 
                  << std::setw(15) << std::left << "iterations" 
                  << std::setw(30) << std::left << "x_opt"<< std::endl;
        std::cout << "---------------------------------------------------------------------------------------------------------------------------" << std::endl;
    }

    void show_results(const std::string& method_name, const std::vector<double>& x_opt, const Parameters& params, const double time, const size_t iter) {
        // Print results with fixed width for proper column alignment
        std::cout << std::setw(35) << std::left << method_name
                  << std::setw(15) << std::fixed << std::setprecision(6) << params.func(x_opt)
                  << std::setw(15) << std::fixed << std::setprecision(6) << norm2(params.grad_func(x_opt))
                  << std::setw(15) << std::fixed << std::setprecision(6) << time
                  << std::setw(15) << std::left << std::setprecision(6) << iter
                  << std::setw(30) << std::left << vectorToString(x_opt)
                  << std::endl;
        std::cout << "---------------------------------------------------------------------------------------------------------------------------" << std::endl;
    }

    void iterations_output(const size_t k, const size_t k_max){
        if(k < k_max){
            std::cout << "The method has converged in " << k << " iterations." << std::endl;
        }
        else{
            std::cout << "The maximum number of iterations (" << k_max << ") has been reached." << std::endl;
        }
    }

    void debugging(size_t k, double step, double residual, double alpha_k){
        // Print the headers
        if (k == 0) {
            std::cout << std::setw(5) << "K" 
                      << std::setw(15) << "Step" 
                      << std::setw(20) << "Residual" 
                      << std::setw(15) << "Alpha_k" << std::endl;
            std::cout << "-------------------------------------------------------------" << std::endl;
        }

        // Print the iteration values with aligned columns
        std::cout << std::setw(5) << k 
                  << std::setw(15) << step
                  << std::setw(20) << residual 
                  << std::setw(15) << alpha_k 
                  << std::endl;
    }
}

#include "utils.hpp"

#endif // VERBOSE_HPP
