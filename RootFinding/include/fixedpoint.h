#ifndef ROOTS_FIXEDPOINT_H
#define ROOTS_FIXEDPOINT_H

#include <rootfinder.h>

namespace roots {

class FixedPoint : public RootFinder
{
public:
    // constructors
    FixedPoint() = default;
    FixedPoint(std::function<double(double)> init_Func);
    FixedPoint(std::function<double(double)> init_Func,
               unsigned int init_max_iter);
    FixedPoint(std::function<double(double)> init_Func,
               double init_precision);
    FixedPoint(std::function<double(double)> init_Func,
               unsigned int init_max_iter, double init_precision);
    FixedPoint(std::function<double(double)> init_Func,
               double init_precision, unsigned int init_max_iter);

    // computational
    double find_root(double guess);

private:
    // intentionally left blank
};

} // namespace roots

#endif // ROOTS_FIXEDPOINT_H
