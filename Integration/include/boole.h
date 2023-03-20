#ifndef INTGRT_BOOLE_H
#define INTGRT_BOOLE_H

#include <integrator.h>

namespace intgrt {

class Boole : public Integrator
{
    // NOTE: only works for fufficiently large number of intervals that are also
    // multiples of std::thread::hardware_concurrecny()*4.0 due to threading
    // implementation and the method only working for numbers of intervals
    // divisible by 4. Will fix later
public:
    using Integrator::Integrator;

    double loop(double start, double end, unsigned intervals) override;

private:
    // intentionally blank
};

}

#endif // INTGRT_BOOLE_H
