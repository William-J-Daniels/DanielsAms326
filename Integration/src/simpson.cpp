#include <simpson.h>

using namespace intgrt;

double Simpson::loop(double start, double end, unsigned intervals)
{
    //assert(intervals%2 == 0);
    double part = 0.0;
    double delta = (end - start) / intervals;
    double current;

    for (unsigned i = 0; i < intervals-1; i+=2)
    {
        current = start + delta*i;
        part += Function(current) +
                4.0 * Function(current + delta) +
                Function(current + 2.0*delta);
    }
    part *= delta/3.0;

    if (intervals%2)
    {
        integral += (5.0 * Function(end) +
                     8.0 * Function(end - delta) -
                     Function(end - 2.0*delta)) * delta/12.0;
    }

    return part;
}
