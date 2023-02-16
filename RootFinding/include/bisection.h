#ifndef BISECTION_H
#define BISECTION_H

#include <functional>
#include <cassert>
#include <limits>
#include <cstdlib>
#include <iostream>

namespace roots{

class Bisection
{
    // A root-finding class that uses the bisection method to approximate roots.
    // Stops upon convergence or after a user-specified number of iterations.
public:
    // constructors
    Bisection() = delete;
    Bisection(std::function<double(double)> init_Func);
    Bisection(std::function<double(double)> init_Func,
              unsigned int init_max_iter);
    Bisection(std::function<double(double)> init_Func,
              double init_precision);
    Bisection(std::function<double(double)> init_Func,
              unsigned int init_max_iter, double init_precision);
    Bisection(std::function<double(double)> init_Func,
              double init_precision, unsigned int init_max_iter);

    // computational
    double find_root(double left_guess, double right_guess);

    // accessors and mutators
    double get_root();
    void reset();

private:
    std::function<double(double)> Function;
    double root;
    bool root_found = false;
    double precision = 1.0e-12;
    unsigned int num_iter = 0;
    unsigned int max_iter = std::numeric_limits<unsigned int>::max();
};

} // namespace roots

#endif // BISECTION_H
