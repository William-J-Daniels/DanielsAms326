#include <huen.h>

using namespace ode;

double Huen::advance(double step)
{
    future = Euler(DiffEq, x, y, step);

    y += step * 0.5 * (y + future.advance(step));
    x += step;

    return y;
}
