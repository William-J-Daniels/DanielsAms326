#ifndef INTERP_LINEAR_H
#define INTERP_LINEAR_H

#include <polynomialinterpolator.h>

namespace interp {

template <class T, class U>
class Linear : public PolynomialInterpolator<T, U>
{
public:
    using PolynomialInterpolator<T, U>::PolynomialInterpolator;

    void find_coefficients() override;

private:
    double Function(double input) override;
};

// header and implimentation cannot be separated in usual way with class
// templates

template <class T, class U>
void Linear<T, U>::find_coefficients()
{
    this->Coefficients = la::Matrix<double>(2, this->xVals.size() - 1);
    // need 2 coefficients for a line
}

template <class T, class U>
double Linear<T, U>::Function(double input)
{
    std::cerr << "another oopsie" << std::endl;
    exit(EXIT_FAILURE);
}

} // namespace interp

#endif // INTERP_LINEAR_H
