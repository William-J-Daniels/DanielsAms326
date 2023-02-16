#include <secondderivative.h>

using namespace diff;

SecondDerivative::SecondDerivative(std::function<double(double)> init_Function)
{
    Function = init_Function;
}

double SecondDerivative::evaluate(double location)
{
    // returns the derivative approximated non-itteratively using step_size
    return (
        (Function(location + step_size) -
         2.0 * Function(location) +
         Function(location - step_size)
        )
        /
        std::pow(step_size, 2)
    );
}
