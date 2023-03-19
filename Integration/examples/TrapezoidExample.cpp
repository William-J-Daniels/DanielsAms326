#include <trapezoid.h>
#include <iostream>
#include <cmath>

double test_func(double in);

int main()
{
    auto Trap = intgrt::Trapezoid(test_func);

    for (int i = 1; i <= 32; i++)
    {
        std::cout << i << ", " << Trap.evaluate(0.0, 2.0*M_PI, i) << std::endl;
    }

    return 0;
}

double test_func(double in)
{
    return std::sin(in);
}

