[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/6eiYEvnG)

# Challenge 1: A gradient method for the minimization of a multivariate function
<p align="center">
  <a href="https://img.shields.io/badge/C%2B%2B-20-blue"><img src="https://img.shields.io/badge/C%2B%2B-20-blue" alt="C++"></a>
  <a href="https://img.shields.io/badge/GNU Make-3.27.6-blue"><img src="https://img.shields.io/badge/GNU Make-4.3-blue" alt="make"></a>
  <a href="https://img.shields.io/badge/clang-18.1.3-blue"><img src="https://img.shields.io/badge/clang-18.1.3-blue" alt="clang"></a>
</p>
With this challenge we weke tasked to implement a gradient-based optimization method to find the minimum of a differentiable multivariate function .

We decided to implement the following methods: 
- Gradient method with different learning rate update methods:
  - Constant Learning Rate
  - Inverse Decay Method
  - Exponential Decay Method
  - Approximate Line Search, using the Armijo Method
- Heavy-ball Method
- ADAM

## Project Structure and Implementation Choices
```
challenge1-gasati/
├── src/
│   ├── main.cpp
│   ├── utils.cpp
│   ├── extra_methods.cpp
├── include/
│   ├── gradient_methods.hpp
│   ├── extra_methods.hpp
|   ├── parameters.hpp
│   ├── tests.hpp
│   ├── utils.hpp
│   ├── verbose.hpp
├── Makefile
├── run
├── LICENSE
└── README.md
```

- Template functions were preferred over a class-based implementation primarily for educational purposes, to deepen understanding of generic programming concepts.
- Extra methods like ADAM and Heavy Ball Method required specific parameters that couldn't be fitted into template functions. consequently, we decided to treat them separately in a dedicated extra_methods file.
- Parameters.hpp is solely used to declare the Parameters struct; parameter values are set by the functions in tests.hpp.
- Optional type parameters were added to the struct definition in the parameters.hpp file to enhance flexibility and adaptability.
- A collection of pre-defined test parameters has been provided in the tests.hpp file, enabling easy access to a variety of test cases for different scenarios (now selectable from the start menu).
- We opted to assess the efficiency of different methods using std::chrono::high_resolution_clock for timing measurements.
- All verbose output has been grouped into a dedicated namespace for better code organization and readibility.
- run is a Linux executable file that automatizes make clean, make distclean and main running procedure.

# Setup (Linux)
### Prerequisites
Ensure you have the following dependencies installed on your Linux environment:
- C++ Compiler (Clang, GCC, MSVC)
- Make

To install all the prerequisites, run the following command:
 ```
 sudo apt update && sudo apt install g++ cmake make
```
(the project was tested using C++ 20, GNU Make 3.27.6, clang 18.1.3)

### Building the Project
Clone the repository:
``` 
git clone https://github.com/PACS-24-25/challenge1-gasati.git
cd challenge1-gasati
```
Build with the Makefile:
```
make
```
Run the program:
```
./main
```

# Notes
## Results
Result for test1: the test case specified in the challenge description.

```
***************************************************************************************************************************
OPTIMIZATION RESULTS - Test 1 (2xy+4x^4+2y^2+2x)
***************************************************************************************************************************
Method                             min value      residual       time           iterations     x_opt
---------------------------------------------------------------------------------------------------------------------------
Inverse Decay                      -0.885694      0.000004       0.000218       30             [-0.541578, 0.270788]
---------------------------------------------------------------------------------------------------------------------------
Exponential Decay                  -0.885694      0.000004       0.000116       30             [-0.541578, 0.270788]
---------------------------------------------------------------------------------------------------------------------------
Constant Rate                      -0.885694      0.000005       0.000019       29             [-0.541578, 0.270788]
---------------------------------------------------------------------------------------------------------------------------
Approx Line Search (Armijo)        -0.885694      0.000005       0.000036       29             [-0.541578, 0.270788]
---------------------------------------------------------------------------------------------------------------------------
Heavy Ball                         -0.885694      0.000047       0.000205       222            [-0.541581, 0.270785]
---------------------------------------------------------------------------------------------------------------------------
ADAM                               -0.885694      0.000754       0.003479       1169           [-0.541521, 0.270760]
---------------------------------------------------------------------------------------------------------------------------
***************************************************************************************************************************
```
## Current issues / Observations
- The gradient method is highly sensitive to the $\alpha_0$ parameter when using the constant, exponential or inverse decay learning rate update methods.
- Exponential decay and inverse decay require a very small $\mu$, significantly lower than the value suggested in the challenge description.
- ADAM performs worse than expected in terms of efficiency and precision on simple functions (test1 and test2) but shows better performance in higher-dimensional cases (test3).

## Idea / Possible Future Development
- Implement an automatic fine tuner
- Implement conjugate gradient method
- Evaluate and compare the memory efficiency of different methods

## Sources / Bibliography
-  Luca Formaggia, Paolo Josph Baioni, Beatrice Crippa. - Challenge 1. A gradient method for the minimization of a
 multivariate function
- [Kingma, D. P., & Ba, J. (2017). Adam: A method for stochastic optimization. arXiv preprint arXiv:1412.6980.](https://arxiv.org/pdf/1412.6980)
- [Prof. Dr. Michael Hintermüller - Nonlinear Optimization](https://ecirtam.net/autoblogs/autoblogs/zythomblogspotfr_2530d81ebaf87a9d212b9c420da28b772b9e5cb4/media/445d3ada.bms-basic-NLP_120609.pdf)
