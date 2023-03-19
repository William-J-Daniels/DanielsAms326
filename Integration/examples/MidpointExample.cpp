#include <midpoint.h>
#include <iostream>
#include <cmath>

double test_func(double in)
{
    return in;
}

int main()
{
    auto MP = intgrt::Midpoint(test_func);

    for (int i = 1; i <= 32; i++)
    {
        std::cout << i << ", " << MP.evaluate(0.0, 1.0, i) << std::endl;
    }

    return 0;
}
