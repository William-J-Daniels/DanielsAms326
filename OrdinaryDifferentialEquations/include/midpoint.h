#ifndef ODE_MIDPOINT_H
#define ODE_MIDPOINT_H

#include <odesolver.h>

namespace ode {

class Midpoint : public Solver
{
public:
    using Solver::Solver;

    double advance(double step) override;

private:
    // intentionally blank
};

}

#endif // ODE_MIDPOINT_H
