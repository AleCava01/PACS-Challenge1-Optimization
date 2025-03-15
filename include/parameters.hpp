#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP
#include <optional>
#include <functional>


struct Parameters {
    std::function<double(const std::vector<double>&)> func;
    std::function<std::vector<double>(const std::vector<double>&)> grad_func;
    
    unsigned int n;              // Dimension
    std::vector<double> x0;      // Initial guess
    double eps_r;                // Residual tolerance
    double eps_s;                // Step tolerance
    unsigned k_max;              // Max number of iterations
    double alpha_zero;           // Initial learning rate
    std::optional<double> mu;    // Optional parameter for exponential and inverse decay methods
    std::optional<double> sigma; // Optional parameter for the Approximate line search method with Armijo rule

};

#endif // PARAMETERS_HPP