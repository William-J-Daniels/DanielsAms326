#include <midpoint.h>
#include <iostream>

double test_func(double in)
{
    return in;
}

int main()
{
    auto MP = intgrt::Midpoint(test_func);

    std::cout << MP.evaluate(0.0,10.0, 999999999);

    return 0;
}
