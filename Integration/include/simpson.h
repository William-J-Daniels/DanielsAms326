#ifndef INTGRT_SIMPSON_H
#define INTGRT_SIMPSON_H

#include <integrator.h>

namespace intgrt {

class Simpson : public Integrator
{
public:
    using Integrator::Integrator;

    double loop(double start, double end, unsigned intervals) override;

private:
    // intentionally blank
};

}

#endif // INTGRT_SIMPSON_H
