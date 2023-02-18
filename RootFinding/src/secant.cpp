#include <secant.h>

using namespace roots;

Secant::Secant(std::function<double(double)> init_Func)
{
    Function = init_Func;
}

Secant::Secant(std::function<double(double)> init_Func,
               unsigned int init_max_iter)
{
    assert(init_max_iter > 0);

    Function = init_Func;
    max_iter = init_max_iter;
}

Secant::Secant(std::function<double(double)> init_Func,
               double init_precision)
{
    assert(init_precision > 0.0);

    Function = init_Func;
    precision = init_precision;
}

Secant::Secant(std::function<double(double)> init_Func,
               unsigned int init_max_iter, double init_precision)
{
    assert(init_max_iter > 0 && init_precision > 0.0);

    Function = init_Func;
    max_iter = init_max_iter;
    precision = init_precision;
}

Secant::Secant(std::function<double(double)> init_Func,
               double init_precision, unsigned int init_max_iter)
{
    assert(init_precision > 0.0 && init_max_iter > 0);

    Function = init_Func;
    precision = init_precision;
    max_iter = init_max_iter;
}

double Secant::find_root(double left_guess, double right_guess)
{
    assert(right_guess > left_guess);

    root = left_guess;
    double previous = right_guess, elder;

    do
    {
        elder = previous;
        previous = root;

        root = previous - (Function(previous) * (previous - elder)) /
               (Function(previous) - Function(elder));
        num_iter = num_iter + 1;
    } while (std::abs(root - previous) > precision);

    root_found = true;
    return root;
}
