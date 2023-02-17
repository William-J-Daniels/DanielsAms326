#ifndef ROOTFINDER_NEWTONRAPHSON_H
#define ROOTFINDER_NEWTONRAPHSON_H

#include <rootfinder.h>
#include <firstderivative.h>

namespace roots {

class NewtonRaphson : RootFinder
{
public:
    // constructors
    NewtonRaphson() = delete;
    // analytic derivative
    NewtonRaphson(std::function<double(double)> init_Func,
                  std::function<double(double)> init_AnalyticDerivative);
    NewtonRaphson(std::function<double(double)> init_Func,
                  std::function<double(double)> init_AnalyticDerivative,
                  unsigned int init_max_iter);
    NewtonRaphson(std::function<double(double)> init_Func,
                  std::function<double(double)> init_AnalyticDerivative,
                  double init_precision);
    NewtonRaphson(std::function<double(double)> init_Func,
                  std::function<double(double)> init_AnalyticDerivative,
                  unsigned int init_max_iter, double init_precision);
    NewtonRaphson(std::function<double(double)> init_Func,
                  std::function<double(double)> init_AnalyticDerivative,
                  double init_precision, unsigned int init_max_iter);
    // numerical derivative
    NewtonRaphson(std::function<double(double)> init_Func);
    NewtonRaphson(std::function<double(double)> init_Func,
                  unsigned int init_max_iter);
    NewtonRaphson(std::function<double(double)> init_Func,
                  double init_precision);
    NewtonRaphson(std::function<double(double)> init_Func,
                  unsigned int init_max_iter, double init_precision);
    NewtonRaphson(std::function<double(double)> init_Func,
                  double init_precision, unsigned int init_max_iter);

    // computational
    double find_root(double guess);

private:
    std::function<double(double)> AnalyticDerivative;
    diff::FirstDerivative NumericalDerivative;
    bool has_analytic = false;
};

} // namespace roots

#endif // ROOTFINDER_NEWTONRAPHSON_H
