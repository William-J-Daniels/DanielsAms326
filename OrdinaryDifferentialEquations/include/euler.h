#ifndef ODE_EULER_H
#define ODE_EULER_H

#include <explicitodesolver.h>

namespace ode {

class Euler : public ExplicitSolver
{
public:
    using ExplicitSolver::ExplicitSolver;

    double advance(double step) override;

private:
    // intentionally blank
};

}

#endif // ODE_EULER_H
