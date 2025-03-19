

#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include "../include/parameters.hpp"
#include "../include/functions.hpp"
#include "../include/verbose.hpp"
#include "../include/tests.hpp"

using namespace std;

// Gradient descent with Armijo rule
vector<double> gradient_descent_armijo(vector<double> x0, double beta, double sigma, int max_iter, Parameters& params, size_t& k) {
    vector<double> x = x0;
    double alpha_k;
    for (k = 0; k < max_iter; ++k) {
        vector<double> grad = params.grad_func(x);
        alpha_k = 1.0;  // Initial step size guess
        
        // Compute new candidate x
        vector<double> x_new(x.size());
        for (size_t i = 0; i < x.size(); ++i) {
            x_new[i] = x[i] - alpha_k * grad[i];
        }
        
        // Backtracking line search (Armijo condition)
        double grad_norm_sq = 0.0;
        for (double gi : grad) {
            grad_norm_sq += gi * gi;
        }
        
        while (params.func(x_new) > params.func(x) - sigma * alpha_k * grad_norm_sq) {
            alpha_k *= beta;
            for (size_t i = 0; i < x.size(); ++i) {
                x_new[i] = x[i] - alpha_k * grad[i];
            }
        }
        
        // Update x
        x = x_new;
        
        cout << "Iteration " << k + 1 << ": x = [";
        for (double xi : x) {
            cout << xi << " ";
        }
        cout << "], f(x) = " << params.func(x) << ", alpha_k = " << alpha_k << endl;
        
        // Stopping criterion (gradient close to zero)
        if (sqrt(grad_norm_sq) < 1e-6) {
            break;
        }
    }
    return x;
}

int main() {
    Parameters test_params = test1();
    double beta = 0.5;  // Step size reduction factor
    double sigma = 0.5; // Armijo condition parameter
    int max_iter = 100;
    size_t k = 0; // Iterations counter
    
    auto start = chrono::high_resolution_clock::now();
    vector<double> result = gradient_descent_armijo(test_params.x0, beta, sigma, max_iter, test_params,k);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    verbose::print_header_result();
    verbose::show_results("Gradient Descent (Armijo)", result, test_params, elapsed.count(), k);
    return 0;
}






/* #include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include "../include/parameters.hpp"
#include "../include/verbose.hpp"
#include "../include/utility_functions.hpp"
#include "../include/tests.hpp"

void lr_approx_line_search(double& alpha_k, size_t& k, Parameters& params, std::vector<double>& x) {
    alpha_k = 1;
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

};

void lr_armijo_line_search(double& alpha_k, size_t& k, ){

}

template <typename LRUpdateMethod>
std::vector<double> eval(Parameters& params, LRUpdateMethod alpha_update, size_t& k) {
    k = 0; // reset iterations counter
    double alpha_k=1;
    std::vector<double> x = params.x0;
    std::vector<double> x_old = x;
    double grad_norm_sq = 0;
    std::vector<double> grad;


    do{
        x_old = x; // make of x before updating it
        std::vector<double> grad_result = params.grad_func(x); // evaluate the function gradient at the current position x

        for(size_t i = 0; i<x.size(); ++i){
            x[i] -= alpha_k * grad_result[i]; // x vector update, see gradient method algorithm
        }
        
        alpha_update(alpha_k, k, params, x); // update the step size alpha_k

        verbose::debugging(k,norm2(vec_subtract(x,x_old)),norm2(params.grad_func(x)),alpha_k);
        
        k++;

    }while(norm2(vec_subtract(x,x_old))>=params.eps_s && k<params.k_max && norm2(params.grad_func(x))>=params.eps_r);  // stoping conditions: 1) step tolerance; 2) maximum number of iterations 3) residual tolerance

    //verbose::iterations_output(k, params.k_max);
    
    return x;

}

int main(){
    size_t iter = 0;
    Parameters test_params = test1();
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<double> result = eval(test_params, lr_approx_line_search, iter);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    verbose::print_header_result();
    //show_results(const std::string& method_name, const std::vector<double>& x_opt, const Parameters& params, const double time, const size_t iter)
    verbose::show_results("Armijo", result, test_params, elapsed.count(), iter);

    return 0;
} */