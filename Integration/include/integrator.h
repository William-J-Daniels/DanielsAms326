#ifndef INTGRT_INTEGRATOR_H
#define INTGRT_INTEGRATOR_H

#include <functional>
#include <cassert>
#include <thread>

namespace intgrt {

class Integrator
{
    // abstract class
public:
    Integrator(std::function<double(double)> init_Func);
    virtual ~Integrator() = default;

    virtual double evaluate(double start, double end, unsigned intervals) = 0;
    double converge(double start, double end, unsigned intervals,
                    unsigned max_iter);

    void reset();
    double get_integral();
    unsigned get_num_iter();

protected:
    std::function<double(double)> Function;
    double integral = 0.0;
    unsigned num_iter = 1;
    double precision = 1.0e-8;
};

} // namepsace intgrt

#endif // INTGRT_INTEGRATOR_H
