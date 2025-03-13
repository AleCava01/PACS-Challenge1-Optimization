#include<iostream>
#include<vector>



struct parameters
{
    //func
    //grad_func
    unsigned int n;
    std::vector<double> x0;
    double eps_r;
    double eps_s;
    unsigned k_max;
    std::vector<bool> stopping_condition[3],lr_uploate_method[3];
    double int_alpha,sigma;
};


int main(){
    
    return 0;

}