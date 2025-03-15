#ifndef VERBOSE_HPP
#define VERBOSE_HPP

#include <iostream>
#include <vector>
#include "functions.hpp"

namespace verbose {
    void show_results(const std::vector<double>& x_opt, const parameters& params) {
        std::cout << "-------------------------------------------------" << std::endl;
        std::cout << "OPTIMIZATION RESULTS " << std::endl;
        std::cout << "x = ";
        print_vec(x_opt);
        std::cout << "Minimum Function Value: " << params.func(x_opt) << std::endl;
        std::cout << "-------------------------------------------------" << std::endl;
    }
}

#endif // VERBOSE_HPP