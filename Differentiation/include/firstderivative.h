#ifndef DIFF_FIRSTDERIVATIVE_H
#define DIFF_FIRSTDERIVATIVE_H

#include <differentiator.h>

namespace diff {

class FirstDerivative : public Differentiator
{
public:
    FirstDerivative() = default;
    FirstDerivative(std::function<double(double)> init_Function);

    using Differentiator::evaluate;
    double evaluate(double location) override;

private:
    // intentionally left blank
};

} // namespace diff

#endif // DIFF_FIRSTDERIVATIVE_H
