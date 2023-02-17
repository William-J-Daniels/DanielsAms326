#include <firstderivative.h>

using namespace diff;

FirstDerivative::FirstDerivative(std::function<double(double)> init_Function)
{
    Function = init_Function;
}

double FirstDerivative::evaluate(double location)
{
    // returns the derivative approximated non-itteratively using step_size
    return (
        (Function(location + step_size) -
         Function(location - step_size)
        )
        /
        (2.0 * step_size)
    );
}
