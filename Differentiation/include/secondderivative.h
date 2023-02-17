#ifndef DIFF_SECONDDERIVATIVE_H
#define DIFF_SECONDDERIVATIVE_H

#include <differentiator.h>

namespace diff {

class SecondDerivative : public Differentiator
{
public:
    SecondDerivative() = default;
    SecondDerivative(std::function<double(double)> init_Function);

    using Differentiator::evaluate;
    double evaluate(double location) override;

private:
    // intentionally left blank
};

} // namespace diff

#endif // DIFF_SECONDDERIVATIVE_H
