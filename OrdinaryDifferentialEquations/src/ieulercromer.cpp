#include <ieulercromer.h>

using namespace ode;

double iEulerCromer::advance(double step)
{
    x += step;
    y += step * RootFinder.find_root(0.333);

    return y;
}
