#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include <functional>
#include <iostream>
#include <cassert>
#include <cmath>

namespace diff {

class Differentiator
{
    // abstract class for first and second order numerical differentiation
public:
    // can construct defaultly or by passing the function
    Differentiator();
    Differentiator(std::function<double(double)> init_Function);

    // solvers
    double evaluate(double location);
    double evaluate(double location, double new_step_size);
    double converge(double location);
    double converge(double location, double new_precision);

    // mutators
    double get_deriv();
    void reset();

protected:
    std::function<double(double)> Function; // function to be differentiated
    double step_size = 1.0e-6; // default initail step size
    double precision = 1.0e-12; // precision attempted to converge to
    double result; // the approximated derivative
    bool deriv_found = false;
};

} // namespace will

#endif // DIFFERENTIATOR_H
