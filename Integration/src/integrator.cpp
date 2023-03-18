#include <integrator.h>


using namespace intgrt;

Integrator::Integrator(std::function<double(double)> init_Func)
{
    Function = init_Func;
}

double Integrator::evaluate(double start, double end, unsigned intervals)
{
    unsigned start_int, end_int;
    double a_start, a_end;
    auto mod = intervals%std::thread::hardware_concurrency();
    std::vector<std::future<double>> Partials(std::thread::hardware_concurrency());

    for (unsigned i = 0; i < std::thread::hardware_concurrency(); i++)
    {
        start_int = (intervals/std::thread::hardware_concurrency())*i;
        end_int   = (intervals/std::thread::hardware_concurrency())*(i+1);
        if (mod)
        {
            if (i < mod)
            {
                start_int += i;
                end_int   += i+1;
            } else {
                start_int += i;
                end_int   += i;
            }
        } else {
            start_int += mod*(i+1);
            end_int   += mod*(i+1);
        }
        a_start = start + ((end-start)/intervals)*start_int;
        a_end   = start + ((end-start)/intervals)*end_int;
        Partials[i] = std::async(
            &Integrator::loop, this, a_start, a_end, end_int-start_int
        );
    }

    for (auto& p : Partials)
    {
        integral += p.get();
    }

    return integral;
}

double Integrator::converge(double start, double end, unsigned intervals,
                    unsigned max_iter)
{
    double last_integral;
    do
    {
        last_integral = integral;
        evaluate(start, end, intervals*num_iter);
        num_iter++;
    } while (std::abs(last_integral - integral) > precision
             && num_iter < max_iter);

    return integral;
}

void Integrator::reset()
{
    integral = 0.0;
    num_iter = 1;
}

void Integrator::set_precision(double new_precision)
{
    precision = new_precision;
}

double Integrator::get_integral()
{
    return integral;
}

unsigned Integrator::get_num_iter()
{
    return num_iter;
}
