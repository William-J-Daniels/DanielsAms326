#ifndef ODESOLVER_H
#define ODESOLVER_H

#include <functional>
#include <cassert>

class Solver
{
public:
    Solver() = default;
    virtual ~Solver(){ }

    virtual double advance(double step) = 0;
    double advance_steps(int num_steps);

    double get_x() { return x; }
    double get_y() { return y; }
    void set_state(double new_x, double new_y);

protected:
    double x, y, step_size;
};

#endif // ODESOLVER_H
