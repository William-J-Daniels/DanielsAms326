#ifndef ROOTFINDER_BISECTION_H
#define ROOTFINDER_BISECTION_H

#include <rootfinder.h>

namespace roots{

class Bisection : public RootFinder
{
    // A root-finding class that uses the bisection method to approximate roots.
    // Stops upon convergence or after a user-specified number of iterations.
public:
    // constructors
    Bisection() = default;
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

private:
    // intentionally blank
};

} // namespace roots

#endif // ROOTFINDER_BISECTION_H
