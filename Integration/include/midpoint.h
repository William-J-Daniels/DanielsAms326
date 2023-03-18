#ifndef INTGRT_MIDPOINT_H
#define INTGRT_MIDPOINT_H

#include <integrator.h>

namespace intgrt {

class Midpoint : public Integrator
{
public:
    using Integrator::Integrator;

    double loop(double start, double end, unsigned intervals) override;

private:
    // intentionally blank
};

}

#endif // INTGRT_MIDPOINT_H
