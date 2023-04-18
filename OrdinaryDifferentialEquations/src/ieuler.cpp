#include <ieuler.h>

using namespace ode;

double iEuler::advance(double step)
{
    y += step * RootFinder.find_root(0.333);
    x += step;

    return y;
}
