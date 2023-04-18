#ifndef EXPLICIT_ODE_SOLVER_H
#define EXPLICIT_ODE_SOLVER_H

#include <odesolver.h>

namespace ode {

class ExplicitSolver : public Solver
{
public:
    ExplicitSolver() = default;
    ExplicitSolver(std::function<double(double)> init_DiffEq,
                   double init_x, double init_y,
                   double init_step);
    virtual ~ExplicitSolver(){ }

protected:
    std::function<double(double)> DiffEq;
};

}

#endif // EXPLICIT_ODE_SOLVER_H
