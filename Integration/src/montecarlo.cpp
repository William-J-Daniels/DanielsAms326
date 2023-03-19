#include <montecarlo.h>

using namespace intgrt;

double MonteCarlo::loop(double start, double end, unsigned intervals)
{
    double part = 0.0;
    auto generator = rng::UniformGenerator<double>();

    for (unsigned i = 0; i < intervals; i++)
    {
        part += Function(
            (generator() * (end - start) + start)
        );
    }
    part *= (end - start) / intervals;

    return part;
}
