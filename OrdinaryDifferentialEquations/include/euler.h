#ifndef ODE_EULER_H
#define ODE_EULER_H

#include <odesolver.h>

namespace ode {

class Euler : public Solver
{
public:
    using Solver::Solver;

    double advance(double step) override;

private:
    // intentionally blank
};

}

#endif // ODE_EULER_H
