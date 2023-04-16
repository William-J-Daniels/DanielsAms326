#include <euler.h>

using namespace ode;

double Euler::advance(double step)
{
    y += step * DiffEq(x);
    x += step;

    return y;
}
