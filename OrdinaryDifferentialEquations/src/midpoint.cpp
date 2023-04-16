#include <midpoint.h>

using namespace ode;

double Midpoint::advance(double step)
{
    y += step * DiffEq(x + step/2.0);
    x += step;

    return y;
}
