[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/6eiYEvnG)

# Challenge 1: A gradient method for the minimization of a multivariate function
With this challenge we weke tasked to implement a gradient-based optimization method to find the minimum of a differentiable multivariate function $f:\mathbb R^n \to \mathbb R$.

We decided to implement the following methods: 
- Gradient method with different learning rate update methods:
  - Constant Learning Rate
  - Inverse Decay Method
  - Exponential Decay Method
  - Approximate Line Search, using the Armijo Method
- ADAM


## Install (Linux)
### Prerequisites
Ensure you have the following dependencies installed on your Linux environment:
- C++ Compiler
- Make

To install all the prerequisites, run the following command:
 ```
 sudo apt update && sudo apt install g++ cmake make
```

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
Running the program:

## Current issues / Observations
- The method is highly sensitive to the $\alpha_0$ parameter when using the exponential or inverse decay learning rate update methods.
- Exponential decay and inverse decay require a very small $\mu$, significantly lower than the value suggested in the challenge description.
- ADAM is much less efficient ad precise than expected

## Idea / Possible Future Development
- Implement an automatic fine tuner
- Implement conjugate gradient method

## Sources
[Kingma, D. P., & Ba, J. (2017). Adam: A method for stochastic optimization. arXiv preprint arXiv:1412.6980.](https://arxiv.org/pdf/1412.6980)
