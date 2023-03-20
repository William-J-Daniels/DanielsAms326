#include <boole.h>

using namespace intgrt;

double Boole::loop(double start, double end, unsigned intervals)
{
    //assert(intervals%2 == 0);
    double part = 7.0 * (Function(start) + Function(end));
    double sub_part;
    double delta = (end - start) / intervals;

    sub_part = 0.0;
    for (unsigned i = 1; i <= intervals-1; i+=2)
    {
        sub_part += Function(start + delta*i);
    }
    part += 32.0*sub_part;

    sub_part = 0.0;
    for (unsigned i = 2; i <= intervals-2; i+=4)
    {
        sub_part += Function(start + delta*i);
    }
    part += 12.0*sub_part;

    sub_part = 0.0;
    for (unsigned i = 4; i <= intervals-4; i+=4)
    {
        sub_part += Function(start + delta*i);
    }
    part += 14.0*sub_part;

    part *= (2.0 * delta)/45.0;

    return part;
}
