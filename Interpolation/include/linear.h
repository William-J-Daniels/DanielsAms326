#ifndef INTERP_LINEAR_H
#define INTERP_LINEAR_H

#include <polynomialinterpolator.h>

namespace interp {

template <class T, class U>
class Linear : public PolynomialInterpolator<T, U>
{
public:
    Linear(T x, U y) : PolynomialInterpolator<T,U>(x,y) {}

    void find_coefficients() override;

private:
    double Function(std::vector<double> input) override;
};

// header and implimentation cannot be separated in usual way with class
// templates

template <class T, class U>
void Linear<T, U>::find_coefficients()
{
    this->Coefficients = la::Matrix<double>(2, this->xVals.size() - 1);
    // need points-1 sets of 2 coefficients for a line
    // row 0 is slope row 1 is intercept

    // for (auto [x, y] = std::tuple{this->xVals.begin(), this->yVals.end()};)
    // {
    //     //
    // }

    // transform is probably the best option, but im out of time to impliment it properly
    // std::transform(this->xVals.begin(), this->xVals.end(), // defines range
    //                this->yVals.begin()), // the other data; we know ranges are =
    //                this->Coefficients.begin());
}

template <class T, class U>
double Linear<T, U>::Function(std::vector<double> input)
{
    return 0;
}

} // namespace interp

#endif // INTERP_LINEAR_H
