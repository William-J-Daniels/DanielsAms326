#ifndef ODE_EULERCROMER_H
#define ODE_EULERCROMER_H

#include <explicitodesolver.h>

namespace ode {

class EulerCromer : public ExplicitSolver
{
public:
    using ExplicitSolver::ExplicitSolver;

    double advance(double step) override;

private:
    // intentionally blank
};

}

#endif // ODE_EULERCROMER_H
