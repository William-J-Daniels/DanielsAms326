#include <odesolver.h>

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
