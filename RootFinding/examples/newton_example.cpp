#include <newtonraphson.h>
#include <cmath>

double MyFunc(double input);

int main()
{
    auto Test = roots::NewtonRaphson(MyFunc);

    std::cout << Test.find_root(3.1415) << std::endl;

    return 0;
}

double MyFunc(double input)
{
    return (std::pow(input-5.4, 2));
}
