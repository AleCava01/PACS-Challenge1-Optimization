#include "../include/extra_methods.hpp"

// --- EXTRA METHODS ---------------------------------------------------------------

// Heavy Ball
std::vector<double> heavy_ball(const Parameters& params, size_t& k,const double eta) {
    
    k = 0; // reset iterations counter
    double alpha_k=params.alpha_zero;//initial learning rate
    std::vector<double> x = params.x0; //initial guess
    std::vector<double> x_old;
    std::vector<double> grad = params.grad_func(x); // evaluate the function gradient at the current position x
    
    std::vector<double> d = vec_scaler(grad,-alpha_k); //initial direction

    do{
        k++;
        x_old = x; // make of x before updating it

        // x_{k+1} = x_k + d_{k+1}
        for(size_t i=0; i<x.size(); ++i){
            x[i] += d[i]; // x vector update, see gradient method algorithm
        }

        std::vector<double> grad_new = params.grad_func(x); // evaluate the function gradient at the current position x

        // Update d_{k+1} = eta*d_k - alpha_k*grad_new
        // First do: d = eta*d
        d = vec_scaler(d,eta);

        // do again: d = d - alpha_k * grad_new
        // note that d is now eta*d_k

        for(size_t i = 0; i<d.size(); ++i){
            d[i] -= alpha_k * grad_new[i]; // d vector update, see gradient method algorithm
            
        }

    }while(norm2(vec_subtract(x,x_old))>=params.eps_s && k<params.k_max && norm2(params.grad_func(x))>=params.eps_r);

    return x;
}

// ADAM
std::vector<double> adam(const Parameters& params, size_t& k, const double beta1, const double beta2, double alpha,const double eps) {
    k = 0; // reset iterations counter
    auto x = params.x0;
    std::vector<double> m(x.size(), 0.0);
    std::vector<double> v(x.size(), 0.0);
    std::vector<double> grad_squared;
    auto m_scaled = m;
    auto v_scaled = v;
    std::vector<double> grad;
    std::vector<double> x_old = x;

    do{
        k++;
        x_old = x;
        grad = params.grad_func(x);

        m = vec_sum(vec_scaler(m,beta1), vec_scaler(grad,1-beta1));
        grad_squared = ew_square(grad); // hadamard (element wise) product of grad * grad
        v = vec_sum(vec_scaler(v,beta2), vec_scaler(grad_squared,1-beta2));

        m_scaled = vec_scaler(m,(1/(1-std::pow(beta1,k))));
        v_scaled = vec_scaler(v,(1/(1-std::pow(beta2,k))));

        for(size_t i=0; i<x.size(); ++i){
            x[i] -= alpha*m_scaled[i]/(std::sqrt(v_scaled[i])+eps);
        }

    }while(norm2(vec_subtract(x,x_old))>=params.eps_s && k<params.k_max && norm2(params.grad_func(x))>=params.eps_r);

    return x;
}