#include <odesolver.h>

using namespace ode;

Solver::Solver(std::function<double(double)> init_DiffEq,
               double init_x, double init_y,
               double init_step)
{
    assert(init_step != 0.0);

    DiffEq    = init_DiffEq;
    x = init_x;
    y = init_y;
    step_size = init_step;
}

double Solver::advance_steps(int num_steps)
{
    assert(num_steps != 0);

    for (int i = 0; i < num_steps; i++)
    {
        advance(step_size);
    }

    return x;
}

void Solver::set_state(double new_x, double new_y)
{
    x = new_x;
    y = new_y;
}
