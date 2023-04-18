#ifndef ODE_HUEN_H
#define ODE_HUEN_H

#include <explicitodesolver.h>
#include <euler.h>

namespace ode {

class Huen : public ExplicitSolver
{
public:
    using ExplicitSolver::ExplicitSolver;

    double advance(double step) override;

private:
    Euler future;
};

}

#endif // ODE_HUEN_H
