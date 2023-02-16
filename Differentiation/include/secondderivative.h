#ifndef DIFF_SECONDDERIVATIVE_H
#define DIFF_SECONDDERIVATIVE_H

#include <differentiator.h>

namespace diff {

class SecondDerivative : public Differentiator
{
public:
    SecondDerivative() = delete;
    SecondDerivative(std::function<double(double)> init_Function);

    using Differentiator::evaluate;
    double evaluate(double location);
    using Differentiator::converge;

private:
    // intentionally left blank
};

} // namespace diff

#endif // DIFF_SECONDDERIVATIVE_H
