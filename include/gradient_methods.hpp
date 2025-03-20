#ifndef GRADIENT_METHODS_HPP
#define GRADIENT_METHODS_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "parameters.hpp"
#include "verbose.hpp"
#include "utils.hpp"

// --- LEARNING RATE UPDATE FUNCTIONS -----------------------------------------------

// No update, keeps alpha constant
void lr_constant(const double& alpha_k, size_t& k, const Parameters& params,const std::vector<double>& x){}

// Exponential decay learning rate
void lr_exp_decay(double& alpha_k, size_t& k, const Parameters& params,const std::vector<double>& x){
    alpha_k = params.alpha_zero * std::exp(-(*params.mu) * k);
}

// Inverse decay learning rate
void lr_inv_decay(double& alpha_k, size_t& k, const Parameters& params,const std::vector<double>& x){
    alpha_k = params.alpha_zero / (1+ (*params.mu) * k);
}

// Approximate line search using Armijo rule
void lr_approx_line_search(double& alpha_k, size_t& k, const Parameters& params,const std::vector<double>& x) {
    
    std::vector<double> grad = params.grad_func(x);
    double grad_norm_sq = 0;
    for(size_t i = 0; i<grad.size(); ++i){grad_norm_sq += (grad[i]*grad[i]);}
    double alpha_min = 1e-3;
    auto armijo_condition = [&params](const auto& x, const auto& grad, double alpha_k, double grad_norm_sq) {
        return params.func(x) - params.func(vec_subtract(x, vec_scaler(grad, alpha_k))) >= (*params.sigma) * alpha_k * grad_norm_sq;
    };
    while (!armijo_condition(x, grad, alpha_k,grad_norm_sq) && alpha_k > alpha_min) {
        alpha_k /= 2;
    }
}

// --- GRADIENT METHOD IMPLEMENTATION  ---------------------------------------------

template <typename LRUpdateMethod>
std::vector<double> eval(const Parameters& params, LRUpdateMethod alpha_update, size_t& k) {
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

#endif // GRADIENT_METHODS_HPP


