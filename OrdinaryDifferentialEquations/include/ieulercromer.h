#ifndef ODE_IEULERCROMER_H
#define ODE_IEULERCROMER_H

#include <implicitodesolver.h>

namespace ode {

class iEulerCromer : public iSolver
{
public:
    using iSolver::iSolver;

    double advance(double step) override;

private:
    // intentionally blank
};

}

#endif // ODE_IEULERCROMER_H
