#ifndef ODE_HUEN_H
#define ODE_HUEN_H

#include <odesolver.h>
#include <euler.h>

namespace ode {

class Huen : public Solver
{
public:
    using Solver::Solver;

    double advance(double step) override;

private:
    Euler future;
};

}

#endif // ODE_HUEN_H
