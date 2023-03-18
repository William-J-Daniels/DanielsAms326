#include <integrator.h>

using namespace intgrt;

Integrator::Integrator(std::function<double(double)> init_Func)
{
    Function = init_Func;
}

double Integrator::converge(double start, double end, unsigned intervals,
                    unsigned max_iter)
{
    double last_integral;
    do
    {
        last_integral = integral;
        evaluate(start, end, intervals*num_iter);
        num_iter++;
    } while (std::abs(last_integral - integral) > precision
             && num_iter < max_iter);

    return integral;
}

void Integrator::reset()
{
    integral = 0.0;
    num_iter = 1;
}

double Integrator::get_integral()
{
    return integral;
}

unsigned Integrator::get_num_iter()
{
    return num_iter;
}
