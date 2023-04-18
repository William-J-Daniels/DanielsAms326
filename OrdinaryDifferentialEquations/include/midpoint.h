#ifndef ODE_MIDPOINT_H
#define ODE_MIDPOINT_H

#include <explicitodesolver.h>

namespace ode {

class Midpoint : public ExplicitSolver
{
public:
    using ExplicitSolver::ExplicitSolver;

    double advance(double step) override;

private:
    // intentionally blank
};

}

#endif // ODE_MIDPOINT_H
