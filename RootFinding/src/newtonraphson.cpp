#include <newtonraphson.h>

using namespace roots;

NewtonRaphson::NewtonRaphson(std::function<double(double)> init_Func,
                  std::function<double(double)> init_AnalyticDerivative)
{
    Function = init_Func;
    AnalyticDerivative = init_AnalyticDerivative;
    has_analytic = true;
}

NewtonRaphson::NewtonRaphson(std::function<double(double)> init_Func,
                             std::function<double(double)> init_AnalyticDerivative,
                             unsigned int init_max_iter)
{
    assert(init_max_iter > 0);

    Function = init_Func;
    AnalyticDerivative = init_AnalyticDerivative;
    max_iter = init_max_iter;
    has_analytic = true;
}

NewtonRaphson::NewtonRaphson(std::function<double(double)> init_Func,
                             std::function<double(double)> init_AnalyticDerivative,
                             double init_precision)
{
    assert(init_precision > 0.0);

    Function = init_Func;
    AnalyticDerivative = init_AnalyticDerivative;
    precision = init_precision;
    has_analytic = true;
}

NewtonRaphson::NewtonRaphson(std::function<double(double)> init_Func,
                             std::function<double(double)> init_AnalyticDerivative,
                             unsigned int init_max_iter, double init_precision)
{
    assert(init_precision > 0.0 && init_max_iter > 0);

    Function = init_Func;
    AnalyticDerivative = init_AnalyticDerivative;
    precision = init_precision;
    max_iter = init_max_iter;
    has_analytic = true;
}

NewtonRaphson::NewtonRaphson(std::function<double(double)> init_Func,
                             std::function<double(double)> init_AnalyticDerivative,
                             double init_precision, unsigned int init_max_iter)
{
    assert(init_max_iter > 0 && init_precision > 0.0);

    Function = init_Func;
    AnalyticDerivative = init_AnalyticDerivative;
    max_iter = init_max_iter;
    precision = init_precision;
    has_analytic = true;
}

NewtonRaphson::NewtonRaphson(std::function<double(double)> init_Func)
{
    Function = init_Func;
    NumericalDerivative = diff::FirstDerivative(Function);
}

NewtonRaphson::NewtonRaphson(std::function<double(double)> init_Func,
                             unsigned int init_max_iter)
{
    assert(init_max_iter);

    Function = init_Func;
    NumericalDerivative = diff::FirstDerivative(Function);
    max_iter = init_max_iter;
}

NewtonRaphson::NewtonRaphson(std::function<double(double)> init_Func,
                             double init_precision)
{
    assert(init_precision > 0.0);

    Function = init_Func;
    NumericalDerivative = diff::FirstDerivative(Function);
    precision = init_precision;
}

NewtonRaphson::NewtonRaphson(std::function<double(double)> init_Func,
                             unsigned int init_max_iter, double init_precision)
{
    assert(init_precision > 0.0 && init_max_iter > 0);

    Function = init_Func;
    NumericalDerivative = diff::FirstDerivative(Function);
    precision = init_precision;
    max_iter = init_max_iter;
}

NewtonRaphson::NewtonRaphson(std::function<double(double)> init_Func,
                             double init_precision, unsigned int init_max_iter)
{
    assert(init_max_iter > 0 && init_precision > 0.0);

    Function = init_Func;
    NumericalDerivative = diff::FirstDerivative(Function);
    max_iter = init_max_iter;
    precision = init_precision;
}

double NewtonRaphson::find_root(double guess)
{
    double previous;
    root = guess;

    if (has_analytic)
    {
        do
        {
            previous = root;
            root = previous - (Function(previous)/AnalyticDerivative(previous));
            num_iter = num_iter + 1;
        } while (std::abs(root - previous) > precision && num_iter < max_iter);
        root_found = true;
        return root;
    }

    do
    {
        previous = root;
        root = previous -
               (Function(previous)/NumericalDerivative.evaluate(previous));
        num_iter = num_iter + 1;
    } while (std::abs(root - previous) > precision && num_iter < max_iter);
    root_found = true;
    return root;
}
