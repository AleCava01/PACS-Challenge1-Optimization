#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "parameters.hpp"
#include "verbose.hpp"


// --- UTILITY FUNCTIONS --------------------------------------------------------------

// Function to subtract two vectors element-wise
std::vector<double> vec_subtract(std::vector<double> &v1, std::vector<double> &v2){
    std::vector<double> result = v1;
    for(unsigned i=0; i<v1.size(); ++i){
        result[i] -= v2[i];
    }
    return result;
};

// L2 Norm (Euclidean norm, sqrt of sum of squares of vector elements)
double norm2(const std::vector<double>& vec){
    double norm = 0.0;
    for(unsigned i=0; i<vec.size(); ++i){
        norm += vec[i]*vec[i];
    }
    return std::sqrt(norm);
};

// Function to print a vector
void print_vec(std::vector<double> x){
    for(int i=0; i<x.size()-1; ++i){
        std::cout <<  x[i] << " , ";
    }
    std::cout << x[x.size()-1];
    std::cout << std::endl;
}



// --- LEARNING RATE UPDATE FUNCTIONS -----------------------------------------------

// No update, keeps alpha constant
void lr_constant(double& alpha_k, unsigned& k, Parameters& params, std::vector<double>& x){}

// Exponential decay learning rate
void lr_exp_decay(double& alpha_k, unsigned& k, Parameters& params, std::vector<double>& x){
    alpha_k = params.alpha_zero * std::exp(-(*params.mu) * k);
}

// Inverse decay learning rate
void lr_inv_decay(double& alpha_k, unsigned& k, Parameters& params, std::vector<double>& x){
    alpha_k = params.alpha_zero / (1+ (*params.mu) * k);
}

// Approximate line search using Armijo rule
void lr_approx_line_search(double& alpha_k, unsigned& k, Parameters& params, std::vector<double>& x){
    
}

// --- GRADIENT METHOD IMPLEMENTATION  ---------------------------------------------

template <typename LRUpdate>
std::vector<double> eval(Parameters& params, LRUpdate alpha_update) {
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

        alpha_update(alpha_k, k, params,x);

        /* DEBUGGING
        print_vec(x); // x vector progression
        std::cout << "alpha_k: " << alpha_k << std::endl;
        std::cout << "K: " << k << " | step: " <<  norm2(vec_subtract(x,x_old)) << " | residual: " << norm2(params.grad_func(x)) << std::endl;
        */
        std::cout << "alpha_k: " << alpha_k << std::endl;
        k++;

    }while(norm2(vec_subtract(x,x_old))>=params.eps_s && k<params.k_max && norm2(params.grad_func(x))>=params.eps_r);  // stoping conditions: 1) step tolerance; 2) maximum number of iterations 3) residual tolerance


    verbose::iterations_output(k, params.k_max);
    

    return x;

}

#endif // FUNCTIONS_HPP