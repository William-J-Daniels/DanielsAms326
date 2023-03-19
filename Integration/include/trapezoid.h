#ifndef INTGRT_TRAPEZOID_H
#define INTGRT_TRAPEZOID_H

#include <integrator.h>

namespace intgrt {

class Trapezoid : public Integrator
{
public:
    using Integrator::Integrator;

    double loop(double start, double end, unsigned intervals) override;

private:
    // intentionally blank
};

}

#endif // INTGRT_TRAPEZOID_H
