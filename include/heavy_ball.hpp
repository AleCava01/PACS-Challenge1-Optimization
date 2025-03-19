#include "parameters.hpp"
#include "utility_functions.hpp" // for vec_scaler, vec_subtract, norm2, etc.
#include "verbose.hpp"

template <typename LRUpdateMethod>
std::vector<double> heavy_ball(Parameters& params, LRUpdateMethod alpha_update, size_t& k,double eta) {
    
    k = 0; // reset iterations counter
    double alpha_k=params.alpha_zero;//initial learning rate
    std::vector<double> x = params.x0; //initial guess
    std::vector<double> x_old = x;//make of x before updating it
    std::vector<double> grad = params.grad_func(x); // evaluate the function gradient at the current position x
    
    std::vector<double> d = vec_scaler(grad,-alpha_k); //initial direction

    for(size_t i=0; i<x.size(); ++i){
        x[i] += d[i]; // x vector update, see gradient method algorithm
    }
 

    do{
        k++;
        x_old = x; // make of x before updating it
        std::vector<double> grad_new = params.grad_func(x); // evaluate the function gradient at the current position x


        // Update d_{k+1} = eta*d_k - alpha_k*grad_new
        // First do: d = eta*d
        d = vec_scaler(d,eta);

        // do again: d = d - alpha_k * grad_new
        // note that d is now eta*d_k

        for(size_t i = 0; i<d.size(); ++i){
            d[i] -= alpha_k * grad_new[i]; // d vector update, see gradient method algorithm
            
        }

        // x_{k+1} = x_k + d_{k+1}
        for(size_t i = 0; i < x.size(); ++i) {
            x[i] += d[i];
        }

    }while(norm2(vec_subtract(x,x_old))>=params.eps_s && k<params.k_max && norm2(params.grad_func(x))>=params.eps_r);

    return x;
}
