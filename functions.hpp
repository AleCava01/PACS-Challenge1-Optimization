#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <optional>


struct parameters
{
    std::function<double(const std::vector<double>&)> func;
    std::function<std::vector<double>(const std::vector<double>&)> grad_func;
    unsigned int n; // dimension
    std::vector<double> x0; // initial guess
    double eps_r; // residual tolerance
    double eps_s; // step tolerance
    unsigned k_max; // max number of iterations
    double alpha_zero; // initial learning rate
    std::optional<double> mu; // optional parameter for exponential and inverse decay methods
};

// --- UTILITY FUNCTIONS -----------------------------------------------------------------

std::vector<double> vec_subtract(std::vector<double> &v1, std::vector<double> &v2){
    std::vector<double> result = v1;
    for(unsigned i=0; i<v1.size(); ++i){
        result[i] -= v2[i];
    }
    return result;
};

double norm1(const std::vector<double>& vec){
    // implements the L1 Norm
    double norm = 0.0;
    for(unsigned i=0; i<vec.size(); ++i){
        norm += std::abs(vec[i]);
    }
    return norm;
};

double norm2(const std::vector<double>& vec){
    // implements the L2 Norm
    double norm = 0.0;
    for(unsigned i=0; i<vec.size(); ++i){
        norm += vec[i]*vec[i];
    }
    return std::sqrt(norm);
};

void print_vec(std::vector<double> x){
    for(int i=0; i<x.size()-1; ++i){
        std::cout <<  x[i] << " , ";
    }
    std::cout << x[x.size()-1];
    std::cout << std::endl;
}

// --- CORE FUNCTIONS  -------------------------------------------------------------------

// --- --- Learning Rate Update functions ------------------------------------------------

void lr_exp_decay(double& alpha_k, unsigned& k, parameters& params){
    alpha_k = params.alpha_zero * std::exp(-(*params.mu) * k);
}
void lr_inv_decay(double& alpha_k, unsigned& k, parameters& params){
    alpha_k = params.alpha_zero / (1+ (*params.mu) * k);
}
void lr_approx_line_search(double& alpha_k, unsigned& k, parameters& params){
    // Armijo rule
}
void lr_constant(double& alpha_k, unsigned& k, parameters& params){
    // does nothing
}

// --- --- Gradient descent implementation -----------------------------------------------

template <typename LRUpdate>
std::vector<double> eval(parameters& params, LRUpdate alpha_update) {
    double alpha_k=params.alpha_zero;
    std::vector<double> x = params.x0;
    std::vector<double> x_old = x;
    unsigned k = 0; // iterations counter

    do{
        x_old = x; // make of x before updating it
        std::vector<double> grad_result = params.grad_func(x); // evaluate the function gradient at the current position x

        for(unsigned i = 0; i<x.size(); ++i){
            x[i] -= alpha_k * grad_result[i]; // x vector update, see gradient method algorithm
        }

        alpha_update(alpha_k, k, params);

        /* DEBUGGING
        print_vec(x); // x vector progression
        std::cout << "alpha_k: " << alpha_k << std::endl;
        std::cout << "K: " << k << " | step: " <<  norm2(vec_subtract(x,x_old)) << " | residual: " << norm2(params.grad_func(x)) << std::endl;
        */
        std::cout << "alpha_k: " << alpha_k << std::endl;
        k++;

    }while(norm2(vec_subtract(x,x_old))>=params.eps_s && k<params.k_max && norm2(params.grad_func(x))>=params.eps_r);  // stoping conditions: 1) step tolerance; 2) maximum number of iterations 3) residual tolerance


    if(k<params.k_max){
        std::cout << "The method has converged in " << k << " iterations." << std::endl;
    }
    else{
        std::cout << "The maximum number of iterations (" << params.k_max << ") has been reached." << std::endl;
    }

    return x;

}

#endif // FUNCTIONS_HPP