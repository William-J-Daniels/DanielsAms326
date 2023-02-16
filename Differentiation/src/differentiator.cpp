#include <differentiator.h>

using namespace diff;

// constructors

Differentiator::Differentiator()
{
    // intentionally left blank
}

Differentiator::Differentiator(std::function<double(double)> init_Function)
{
    Function = init_Function;
}

// solvers
// using time step

double Differentiator::evaluate(double location)
{
    std::cerr << "Differentiator is an abstract class not intneded for direct "
              << "use in programs." << std::endl;
    exit(EXIT_FAILURE);
}

double Differentiator::evaluate(double location, double new_step_size)
{
    // overload of evaluate that also sets a new step size
    step_size = new_step_size;
    return evaluate(location);
}

// iterative

double Differentiator::converge(double location)
{
    // iteratively reduces the step size until precision is achieved
    double last_result;
    result = evaluate(location);
    do
    {
        last_result = result;
        step_size = step_size / 2.0;
        result = evaluate(location);
        std::cout << result << std::endl;
    } while (std::abs(result - last_result) > precision);
    return result;
}

double Differentiator::converge(double location, double new_precision)
{
    precision = new_precision;
    return converge(location);
}
// mutators

double Differentiator::get_deriv()
{
    return result;
}

void Differentiator::reset()
{
    step_size = 1.0e-6;
    precision = 1.0e-12;
}
