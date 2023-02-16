#ifndef DIFF_NEWTONRAPHSON_H
#define DIFF_NEWTONRAPHSON_H

#include <functional>
#include <cassert>
#include <limits>

namespace roots {

class NewtonRaphson
{
public:
    //

private:
    std::function<double(double)> Function;
    double root;
    bool root_found = false;
    double precision = 1.0e-12;
    unsigned int num_iter = 0;
    unsigned int max_iter = std::numeric_limits<unsigned int>::max();
};

} // namespace roots

#endif // DIFF_NEWTONRAPHSON_H
