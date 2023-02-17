#include <fixedpoint.h>
#include <cmath>

double MyFunction(double input);

int main()
{
    auto MyFinder = roots::FixedPoint(MyFunction);

    std::cout << MyFinder.find_root(0.5) << std::endl;

    return 0;
}

double MyFunction(double input)
{
    return (
        (1.0 + 2.0 * std::pow(input, 3))
        /
        (1.0 + 3.0 * std::pow(input, 2))
    );
}

