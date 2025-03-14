#include<iostream>
#include<vector>
#include<cmath>
#include <functional>


struct parameters
{
    std::function<double(double)> func;
    std::function<double(double)> grad_func;
    unsigned int n; // dimension
    std::vector<double> x0; // initial guess
    double eps_r; // residual tolerance
    double eps_s; // step tolerance
    unsigned k_max; // max number of iterations
    unsigned lr_update_method; // update method for the learning rate alpha_k
    double alpha_zero; // initial learning rate
};

std::vector<double> vec_subtract(std::vector<double> &v1, std::vector<double> &v2){
    std::vector<double> result;
    for(unsigned i=0; i<v1.size(); ++i){
        result[i]= v1[i] - v2[i];
    }
    return result;
};

double norm1(const std::vector<double>& vec){
    double norm;
    for(unsigned i=0; i<vec.size(); ++i){
        norm += std::abs(vec[i]);
    }
    return norm;
};

std::vector<double> eval(const parameters& params){ 
    double alpha_k;
    std::vector<double> x = params.x0;
    bool stopping_conditon;
    std::vector<double> x_old;
    x_old = x;
    x_old[0]-=(1+params.eps_s);
    while(norm1(vec_subtract(x,x_old))>params.eps_s){
        x_old = x;
        // do stuff
        std::cout<< "porcodio" << std::endl;
    }
    return x;

}; // must become a function template, see 1.1 Suggestion, first bullet point

// eval function with exponential decay


// eval function with inverse decay

// armijo rule function

// eval function with approximate line search, sigma parameter needed


int main(){

    // test function
    auto f = [](double x[2]) {return 2*x[0]*x[1] + 4*std::pow(x[0],4)+2*std::pow(x[1],2)+2*x[0];};
    double x0[2] = {0.4,4.9};
    std::cout << f(x0) << std::endl;
    
    

    return 0;

}