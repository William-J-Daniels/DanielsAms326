#include <simpson.h>
#include <cmath>
#include <iostream>

double test_func(double in)
{
    return std::sin(in);
}

int main()
{

    auto Simp = intgrt::Simpson(test_func);

    for (int i = 1; i <= 32; i++)
    {
        std::cout << i << ", " << Simp.evaluate(0.0, 2.0*M_PI, i) << std::endl;
    }

    // std::cout << Simp.evaluate(0.0, 1.0, 4);

    return 0;
}
