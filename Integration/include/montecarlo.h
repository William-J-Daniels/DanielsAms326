#ifndef INTRGT_MONTECARLO_H
#define INTRGT_MONTECARLO_H

#include <integrator.h>
#include <uniformgenerator.h>

namespace intgrt {

class MonteCarlo : public Integrator
{
public:
    using Integrator::Integrator;

    double loop(double start, double end, unsigned intervals) override;

private:
    // intentially blank
};

}

#endif // INTRGT_MONTECARLO_H
