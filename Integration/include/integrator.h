#ifndef INTGRT_INTEGRATOR_H
#define INTGRT_INTEGRATOR_H

#include <functional>
#include <cassert>
#include <thread>
#include <future>

namespace intgrt {

class Integrator
{
    // abstract class
public:
    Integrator(std::function<double(double)> init_Func);
    virtual ~Integrator() = default;

    virtual double loop(double start, double end, unsigned intervals) = 0;
    double evaluate(double start, double end, unsigned intervals);
    double converge(double start, double end, unsigned intervals,
                    unsigned max_iter);

    void reset();
    void set_precision(double new_precision);
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
