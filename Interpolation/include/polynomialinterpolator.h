#ifndef INTERP_POLYNOMIALINTERPOLATOR_H
#define INTERP_POLYNOMIALINTERPOLATOR_H

#include <matrix.h>
#include <array>
#include <vector>
#include <list>
#include <cassert>
#include <iostream>
#include <algorithm>

namespace interp {

template <class T, class U>
class PolynomialInterpolator
{
public:
    // constructors and destructor
    PolynomialInterpolator() = default;
    PolynomialInterpolator(T init_xVals,  // accepts std iteratables
                           U init_yVals); // (vector, array, list)
    // input list are assumed to be sorted from low to high xVals
    virtual ~PolynomialInterpolator() = default;

    // computational
    virtual void find_coefficients() = 0;
    double interp_at(double interp_point);

    // accessors and mutators
    la::Matrix<double> get_coefficients();

protected:
    T xVals;
    U yVals;
    virtual double Function(std::vector<double> input) = 0;
    la::Matrix<double> Coefficients;

private:
    // intentionally blank
};

// header and implimentation cannot be separated in usual way with class
// templates

template <class T, class U>
PolynomialInterpolator<T, U>::PolynomialInterpolator(T init_xVals,
                                                     U init_yVals)
{
    try {
        assert(init_xVals.size() == init_yVals.size());
    } catch(...) {
        std::cerr << "Interpolators must be initialized with iterable "
                  << "containers such as std::array, std::vector, or std::list."
                  << std::endl;
        exit(EXIT_FAILURE);
    }
    xVals = init_xVals;
    yVals = init_yVals;
}

template <class T, class U>
la::Matrix<double> PolynomialInterpolator<T, U>::get_coefficients()
{
    return Coefficients;
}

}

#endif // INTERP_POLYNOMIALINTERPOLATOR_H
