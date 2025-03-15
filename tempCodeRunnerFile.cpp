std::vector<double> eval(const parameters& params){ 
    double alpha_k=params.alpha_zero;
    std::vector<double> x = params.x0;
    bool stopping_conditon;
    std::vector<double> x_old;
    x_old = x;
    x_old[0]-=(2*params.eps_s);
    unsigned k = 1;
    while(norm1(vec_subtract(x,x_old))>params.eps_s){
        x_old = x;
        // do stuff
        alpha_k=params.alpha_zero*std::exp(-0.2*k);
        auto grad_result = params.grad_func(x);
        

        std::cout << "-----------------------------" << std::endl;
        std::cout << "x[0] (" << x[0] << ") -= alpha_k (" << alpha_k << ") * grad_func[0] (" << params.grad_func(x_old)[0] << ") ===> = ";
        x[0] = x_old[0] - alpha_k*params.grad_func(x_old)[0];
        std::cout << x[0] << std::endl;
        std::cout << "x[1] (" << x[1] << ") -= alpha_k (" << alpha_k << ") * grad_func[1] (" << params.grad_func(x_old)[1] << ") ===> = ";
        x[1] = x_old[1] - alpha_k*params.grad_func(x_old)[1];
        std::cout << x[1] << std::endl;

        k++;
    }
    return x;

}; // must become a function template, see 1.1 Suggestion, first bullet point
