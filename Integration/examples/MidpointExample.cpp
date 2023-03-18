#include <midpoint.h>
#include <iostream>
#include <cmath>

double test_func(double in)
{
    return std::sin(in);
}

int main()
{
    auto MP = intgrt::Midpoint(test_func);

    std::cout << MP.evaluate(0.0, 2.0*M_PI, 512);

    return 0;
}
