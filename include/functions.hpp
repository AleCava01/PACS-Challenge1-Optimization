#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "parameters.hpp"
#include "verbose.hpp"


// --- UTILITY FUNCTIONS --------------------------------------------------------------

// Function to subtract two vectors element-wise
std::vector<double> vec_subtract(const std::vector<double>& v1, const std::vector<double>& v2){
    std::vector<double> result = v1;
    for(size_t i=0; i<v1.size(); ++i){
        result[i] -= v2[i];
    }
    return result;
};

// L2 Norm (Euclidean norm, sqrt of sum of squares of vector elements)
double norm2(const std::vector<double>& vec){
    double norm = 0.0;
    for(size_t i=0; i<vec.size(); ++i){
        norm += vec[i]*vec[i];
    }
    return std::sqrt(norm);
};

// Function to print a vector
void print_vec(const std::vector<double>& x){
    if (x.empty()){ // Empty vector case
        std::cout << "[]" << std::endl; 
        return;
    }
    std::cout << "[";
    for(size_t i=0; i<x.size()-1; ++i){
        std::cout <<  x[i] << " , ";
    }
    std::cout << x[x.size()-1] << "]" << std::endl;
};

// Function to multiply a vector by a scalar
std::vector<double> vec_scaler(std::vector<double> vec, double x){
    for(size_t i=0; i<vec.size(); ++i){
        vec[i] *= x;
    }
    return vec;
};


// --- LEARNING RATE UPDATE FUNCTIONS -----------------------------------------------

// No update, keeps alpha constant
void lr_constant(double& alpha_k, size_t& k, Parameters& params, std::vector<double>& x){}

// Exponential decay learning rate
void lr_exp_decay(double& alpha_k, size_t& k, Parameters& params, std::vector<double>& x){
    alpha_k = params.alpha_zero * std::exp(-(*params.mu) * k);
}

// Inverse decay learning rate
void lr_inv_decay(double& alpha_k, size_t& k, Parameters& params, std::vector<double>& x){
    alpha_k = params.alpha_zero / (1+ (*params.mu) * k);
}


// Approximate line search using Armijo rule
void lr_approx_line_search(double& alpha_k, size_t& k, Parameters& params, std::vector<double>& x) {
    
    std::vector<double> grad = params.grad_func(x);
    double grad_norm_sq = std::pow(norm2(grad), 2);
    double alpha_min = 1e-3;
    
    while (params.func(x) - params.func(vec_subtract(x, vec_scaler(grad, alpha_k))) < (*params.sigma) * alpha_k * grad_norm_sq && alpha_k > alpha_min) {
        alpha_k /= 2;
        
        grad = params.grad_func(x);
        grad_norm_sq = std::pow(norm2(grad), 2);
    }
}

// --- GRADIENT METHOD IMPLEMENTATION  ---------------------------------------------

template <typename LRUpdate>
std::vector<double> eval(Parameters& params, LRUpdate alpha_update, size_t& k) {
    k = 0; // reset iterations counter
    double alpha_k=params.alpha_zero;
    std::vector<double> x = params.x0;
    std::vector<double> x_old = x;

    do{
        x_old = x; // make of x before updating it
        std::vector<double> grad_result = params.grad_func(x); // evaluate the function gradient at the current position x

        for(size_t i = 0; i<x.size(); ++i){
            x[i] -= alpha_k * grad_result[i]; // x vector update, see gradient method algorithm
        }

        alpha_update(alpha_k, k, params,x);

        //verbose::debugging(k,norm2(vec_subtract(x,x_old)),norm2(params.grad_func(x)),alpha_k);
        
        k++;

    }while(norm2(vec_subtract(x,x_old))>=params.eps_s && k<params.k_max && norm2(params.grad_func(x))>=params.eps_r);  // stoping conditions: 1) step tolerance; 2) maximum number of iterations 3) residual tolerance

    //verbose::iterations_output(k, params.k_max);
    
    return x;

}

#endif // FUNCTIONS_HPP