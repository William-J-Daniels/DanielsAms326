#include <bisection.h>
#include <cmath>

double MyFunc(double input);

int main()
{
    auto Test = roots::Bisection(MyFunc);

    std::cout << Test.find_root(3.1415, 10.0) << std::endl;

    return 0;
}

double MyFunc(double input)
{
    return input - 5.4;
}
