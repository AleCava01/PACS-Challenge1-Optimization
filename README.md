[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/6eiYEvnG)

# Challenge 1. A gradient method for the minimization of a multivariate function
With this challenge we weke tasked to implement a gradient-based optimization method to find the minimum of a differentiable multivariate function $f:\mathbb R^n \to \mathbb R$.

## Current issues / Observations
- The method is highly sensitive to the $\alpha_0$ parameter when using the exponential or inverse decay learning rate update methods.
- Exponential decay and inverse decay require a very small $\mu$, significantly lower than the value suggested in the challenge description.
- Armijo Rule has to be seen again, it's working very badly
- Number of iterations has to be added to the optimization result table

