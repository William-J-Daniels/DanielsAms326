#include <eulercromer.h>

using namespace ode;

double EulerCromer::advance(double step)
{
    x += step;
    y += step * DiffEq(x);

    return y;
}
