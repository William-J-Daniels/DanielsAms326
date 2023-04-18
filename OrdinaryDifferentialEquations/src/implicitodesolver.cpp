#include <implicitodesolver.h>

using namespace ode;

iSolver::iSolver(std::function<double(double)> init_DiffEq,
                               double init_x, double init_y,
                               double init_step)
{
    assert(init_step != 0.0);

    DiffEq = init_DiffEq;
    RootFinder = roots::NewtonRaphson(init_DiffEq);
    x = init_x;
    y = init_y;
    step_size = init_step;
}
