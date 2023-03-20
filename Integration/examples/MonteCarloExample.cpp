#include <montecarlo.h>
#include <cmath>
#include <iostream>

double test_func(double in)
{
    return std::sin(in);
}

int main()
{
    auto MC = intgrt::MonteCarlo(test_func);

    for (int i = 1; i < 512; i++)
    {
        std::cout << MC.evaluate(0.0, 2.0*M_PI, i) << std::endl;
    }

    return 0;
}
