#include <trapezoid.h>

using namespace intgrt;

double Trapezoid::loop(double start, double end, unsigned intervals)
{
    double part = 0.5 * (Function(start) + Function(end));
    double delta = (end-start)/intervals;

    for (unsigned i = 1; i < intervals; i++)
    {
        part += Function(start + i*delta);
    }

    part *= delta;

    return part;
}
