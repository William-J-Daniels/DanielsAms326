#ifndef ROOTFINER_H
#define ROOTFINER_H

#include <functional>
#include <cassert>
#include <limits>
#include <cstdlib>
#include <iostream>

namespace roots{

class RootFinder
{
    // Abstract class for root finding
public:
    // constructors and destructor
    RootFinder() = default;
    RootFinder(std::function<double(double)> init_Func);
    RootFinder(std::function<double(double)> init_Func,
               unsigned int init_max_iter);
    RootFinder(std::function<double(double)> init_Func,
               double init_precision);
    RootFinder(std::function<double(double)> init_Func,
               unsigned int init_max_iter, double init_precision);
    RootFinder(std::function<double(double)> init_Func,
               double init_precision, unsigned int init_max_iter);

    // computational
    double find_root();

    // accessors and mutators
    double get_root();
    void reset();

protected:
    std::function<double(double)> Function;
    double root;
    bool root_found = false;
    double precision = 1.0e-12;
    unsigned int num_iter = 0;
    unsigned int max_iter = std::numeric_limits<unsigned int>::max();
};

} // namespace roots

#endif // ROOTFINER_H
