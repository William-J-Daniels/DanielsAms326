#include <boole.h>
#include <iostream>
#include <cmath>

double test_func(double in)
{
    return in*in;
}

int main()
{
    auto Boole = intgrt::Boole(test_func);

    for (int i = 16; i <= 32; i++)
    {
        std::cout << i << ", " << Boole.evaluate(0.0, 1.0, i) << std::endl;
    }

    // std::cout << Boole.evaluate(0.0, 1.0, 20);

    return 0;
}
