#ifndef IMPLICITODESOLVER_H
#define IMPLICITODESOLVER_H

#include <odesolver.h>
#include <newtonraphson.h>

namespace ode {

class iSolver : public Solver
{
public:
    iSolver() = default;
    iSolver(std::function<double(double)> init_DiffEq,
                   double init_x, double init_y,
                   double init_step);
    virtual ~iSolver(){ }

protected:
    std::function<double(double)> DiffEq;
    roots::NewtonRaphson RootFinder;
};

} // namepsace ode

#endif // IMPLICITODESOLVER_H
