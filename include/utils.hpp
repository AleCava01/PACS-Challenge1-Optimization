#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

// --- UTILITY FUNCTIONS --------------------------------------------------------------

std::vector<double> vec_subtract(std::vector<double> v1, const std::vector<double>& v2);

std::vector<double> vec_sum(std::vector<double> v1, const std::vector<double>& v2);

std::vector<double> ew_square(std::vector<double>& vec);

double norm2(const std::vector<double>& vec);

void print_vec(const std::vector<double>& x);

std::vector<double> vec_scaler(std::vector<double> vec, double x);

std::string vectorToString(const std::vector<double>& vec);

// ------------------------------------------------------------------------------------

#endif // UTILS_HPP