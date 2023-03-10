#include <rootfinder.h>

using namespace roots;

// constructors

RootFinder::RootFinder(std::function<double(double)> init_Func)
{
    Function = init_Func;
}

RootFinder::RootFinder(std::function<double (double)> init_Func,
                     unsigned int init_max_iter)
{
    assert(max_iter > 0);

    Function = init_Func;
    max_iter = init_max_iter;
}

RootFinder::RootFinder(std::function<double(double)> init_Func,
              double init_precision)
{
    assert(init_precision > 0.0);

    Function = init_Func;
    precision = init_precision;
}

RootFinder::RootFinder(std::function<double(double)> init_Func,
                     unsigned int init_max_iter, double init_precision)
{
    assert(init_max_iter > 0 && init_precision > 0.0);

    Function = init_Func;
    max_iter = init_max_iter;
    precision = init_precision;
}

RootFinder::RootFinder(std::function<double(double)> init_Func,
                     double init_precision, unsigned int init_max_iter)
{
    assert(init_precision > 0.0 && init_max_iter > 0);
    Function = init_Func;
    precision = init_precision;
    max_iter = init_max_iter;
}

// accessors and mutators

double RootFinder::get_root()
{
    assert(root_found);
    return root;
}

unsigned int RootFinder::get_num_iter()
{
    assert(root_found);
    return num_iter;
}

void RootFinder::reset()
{
    root_found = false;
    precision = 1.0e-12;
    num_iter = 0;
    max_iter = std::numeric_limits<unsigned int>::infinity();
}
