#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

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
    //unsigned lr_update_method; // update method for the learning rate alpha_k
};

std::vector<double> vec_subtract(std::vector<double> &v1, std::vector<double> &v2){
    std::vector<double> result = v1;
    for(unsigned i=0; i<v1.size(); ++i){
        result[i] -= v2[i];
    }
    return result;
};

double norm1(const std::vector<double>& vec){
    double norm = 0.0;
    for(unsigned i=0; i<vec.size(); ++i){
        norm += std::abs(vec[i]);
    }
    return norm;
};

void print_vec(std::vector<double> x){
    for(int i=0; i<x.size(); ++i){
        std::cout << " | " << x[i];
    }
    std::cout << " |" << std::endl;
}

// eval must become a function template, see 1.1 Suggestion, first bullet point
std::vector<double> eval(const parameters& params){ 

    double alpha_k=params.alpha_zero;
    std::vector<double> x = params.x0;
    std::vector<double> x_old = x;
    unsigned k = 0; // iterations counter

    do{
        x_old = x; // make of x before updating it
        std::vector<double> grad_result = params.grad_func(x); // evaluate the function gradient at the current position x

        for(unsigned i = 0; i<x.size(); ++i){
            x[i] -= alpha_k*grad_result[i]; // x vector update, see gradient method algorithm
        }

        alpha_k=params.alpha_zero * std::exp(-0.2*k); // alpha_k update (exponential decay rule, mu fixed as 0.2)

        /* DEBUGGING
        print_vec(x); // x vector progression
        std::cout << norm1(params.grad_func(x)) << std::endl; // residual print 
        */

        k++;

    }while(norm1(vec_subtract(x,x_old))>=params.eps_s and k<params.k_max and norm1(params.grad_func(x))>=params.eps_r);
    // stoping conditions: 1) step tolerance; 2) maximum number of iterations 3) residual tolerance

    if(k<params.k_max){
        std::cout << "The method has converged in " << k << " iterations." << std::endl;
    }
    else{
        std::cout << "The maximum number of iterations (" << params.k_max << ") has been reached." << std::endl;
    }

    return x;

};

// eval function with inverse decay

// armijo rule function

// eval function with approximate line search, sigma parameter needed

#endif