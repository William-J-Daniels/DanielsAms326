#ifndef ODE_EULERCROMER_H
#define ODE_EULERCROMER_H

#include <odesolver.h>

namespace ode {

class EulerCromer : public Solver
{
public:
    using Solver::Solver;

    double advance(double step) override;

private:
    // intentionally blank
};

}

#endif // ODE_EULERCROMER_H
