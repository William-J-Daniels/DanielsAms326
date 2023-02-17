#ifndef ROOTS_SECANT_H
#define ROOTS_SECANT_H

#include <rootfinder.h>

namespace roots {

class Secant : public RootFinder
{
public:
    // constructors
    Secant() = default;
    Secant(std::function<double(double)> init_Func);
    Secant(std::function<double(double)> init_Func,
           unsigned int init_max_iter);
    Secant(std::function<double(double)> init_Func,
           double init_precision);
    Secant(std::function<double(double)> init_Func,
           unsigned int init_max_iter, double init_precision);
    Secant(std::function<double(double)> init_Func,
           double init_precision, unsigned int init_max_iter);

    // computational
    double find_root(double left_guess, double right_guess);

private:
    // intentionally blank
};

} // namespace roots

#endif // ROOTS_SECANT_H
