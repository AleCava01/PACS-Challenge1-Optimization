#ifndef UTILITY_FUNCTIONS_HPP
#define UTILITY_FUNCTIONS_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>

// --- UTILITY FUNCTIONS --------------------------------------------------------------

// Function to subtract two vectors element-wise
std::vector<double> vec_subtract(std::vector<double> v1, const std::vector<double>& v2){
    for(size_t i=0; i<v1.size(); ++i){
        v1[i] -= v2[i];
    }
    return v1;
};

// Function to sum two vectors element-wise
std::vector<double> vec_sum(std::vector<double> v1, const std::vector<double>& v2){
    for(size_t i=0; i<v1.size(); ++i){
        v1[i] += v2[i];
    }
    return v1;
};

std::vector<double> ew_square(std::vector<double>& vec){
    std::vector<double> result(vec.size(), 0.0);
    for(size_t i = 0; i<vec.size(); ++i){
        result[i] = vec[i]*vec[i];
    }
    return result;
}

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

// Function that converts vectors into string
std::string vectorToString(const std::vector<double>& vec) {
    std::stringstream ss;
    ss << "["; 
    
    for (size_t i = 0; i < vec.size(); ++i) {
        ss << std::fixed << std::setprecision(6) << vec[i]; // Precision for vector elements
        if (i != vec.size() - 1) {
            ss << ", "; 
        }
    }

    ss << "]"; 
    return ss.str(); 
}

#endif // UTILITY_FUNCTIONS_HPP