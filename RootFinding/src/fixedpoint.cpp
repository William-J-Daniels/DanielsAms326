#include <fixedpoint.h>

using namespace roots;

FixedPoint::FixedPoint(std::function<double(double)> init_Func)
{
    Function = init_Func;
}

FixedPoint::FixedPoint(std::function<double(double)> init_Func,
                       unsigned int init_max_iter)
{
    assert(init_max_iter > 0);

    Function = init_Func;
    max_iter = init_max_iter;
}

FixedPoint::FixedPoint(std::function<double(double)> init_Func,
                       double init_precision)
{
    assert(init_precision > 0.0);

    Function = init_Func;
    precision = init_precision;
}

FixedPoint::FixedPoint(std::function<double(double)> init_Func,
                       unsigned int init_max_iter, double init_precision)
{
    assert(init_max_iter > 0 && init_precision > 0.0);

    Function = init_Func;
    max_iter = init_max_iter;
    precision = init_precision;
}

FixedPoint::FixedPoint(std::function<double(double)> init_Func,
                       double init_precision, unsigned int init_max_iter)
{
    assert(init_precision > 0.0 && init_max_iter > 0);

    Function = init_Func;
    precision = init_precision;
    max_iter = init_max_iter;
}

double FixedPoint::find_root(double guess)
{
    double previous;

    do
    {
        previous = root;
        root = Function(root);
        num_iter = num_iter + 1;
    } while(std::abs(root - previous) > precision);

    root_found = true;
    return root;
}
