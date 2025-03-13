#include<iostream>
#include<vector>
#include<cmath>


struct func{
    double value(){};
};

struct parameters
{
    //func
    //grad_func
    unsigned int n; // dimension
    std::vector<double> x0; // initial guess
    double eps_r; // residual tolerance
    double eps_s; // step tolerance
    unsigned k_max; // max number of iterations
    unsigned lr_update_method; // update method for the learning rate alpha_k
    double alpha_zero; // initial learning rate
};

double eval(parameters params){ return 0.0; }; // must become a function template, see 1.1 Suggestion, first bullet point

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