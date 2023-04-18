#ifndef IEULER_H
#define IEULER_H

#include <implicitodesolver.h>

namespace ode {

class iEuler : public iSolver
{
public:
    using iSolver::iSolver;

    double advance(double step) override;

private:
    // intentionally blank
};

} // namespace ode

#endif // IEULER_H
