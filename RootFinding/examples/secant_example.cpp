#include <secant.h>
#include <cmath>
#include <iostream>

double MyFunction(double input);

int main()
{
    auto MyRoot = roots::Secant(MyFunction);

    std::cout << MyRoot.find_root(-5.0, 5.0) << std::endl;

    return 0;
}

double MyFunction(double input)
{
    return (std::pow(input, 3) + 5);
}
