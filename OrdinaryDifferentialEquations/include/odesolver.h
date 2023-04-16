#ifndef ODE_SOLVER_H
#define ODE_SOLVER_H

#include <functional>
#include <cassert>

namespace ode {

class Solver
{
public:
    Solver() = default;
    Solver(std::function<double(double)> init_DiffEq,
           double init_x, double init_y,
           double init_step);
    virtual ~Solver(){ }

    virtual double advance(double step) = 0;
    double advance_steps(int num_steps);

    double get_x() { return x; }
    double get_y() { return y; }
    void set_state(double new_x, double new_y);

protected:
    std::function<double(double)> DiffEq;
    double x, y, step_size;
};

}

#endif // ODE_SOLVER_H
