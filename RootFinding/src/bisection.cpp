#include <bisection.h>

using namespace roots;

// constructors

Bisection::Bisection(std::function<double(double)> init_Func)
{
    Function = init_Func;
}

Bisection::Bisection(std::function<double (double)> init_Func,
                     unsigned int init_max_iter)
{
    assert(max_iter > 0);

    Function = init_Func;
    max_iter = init_max_iter;
}

Bisection::Bisection(std::function<double(double)> init_Func,
              double init_precision)
{
    assert(init_precision > 0.0);

    Function = init_Func;
    precision = init_precision;
}

Bisection::Bisection(std::function<double(double)> init_Func,
                     unsigned int init_max_iter, double init_precision)
{
    assert(init_max_iter > 0 && init_precision > 0.0);

    Function = init_Func;
    max_iter = init_max_iter;
    precision = init_precision;
}

Bisection::Bisection(std::function<double(double)> init_Func,
                     double init_precision, unsigned int init_max_iter)
{
    assert(init_precision > 0.0 && init_max_iter > 0);
    Function = init_Func;
    precision = init_precision;
    max_iter = init_max_iter;
}

// computational

double Bisection::find_root(double left_guess, double right_guess)
{
    assert(right_guess > left_guess);

    while (0.5 * (right_guess - left_guess) > precision && num_iter < max_iter)
    {
        root = 0.5 * (left_guess + right_guess);

        if (Function(root) == 0.0)
            break;
        if (Function(left_guess) * Function(root) < 0.0)
            right_guess = root;
        else
            left_guess = root;

        num_iter = num_iter + 1;
        std::cout << root << std::endl;
    }
    root_found = true;
    return root;
}
