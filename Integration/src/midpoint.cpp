#include <midpoint.h>

using namespace intgrt;

double Midpoint::loop(double start, double end, unsigned intervals)
{
    double part = 0.0;
    double delta = (end - start) / intervals;

    for (unsigned i = 0; i < intervals; i++)
    {
        part += Function(start + (delta * (i + 0.5)));
    }

    part *= delta;

    return part;
}
