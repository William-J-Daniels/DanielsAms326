#include <linear.h>
#include <iostream>
#include <vector>

int main()
{
    std::vector<double> MyX = {0, 1, 2, 3},
                        MyY = {3, 2, 1, 0};

    auto Test = interp::Linear<std::vector<double>, std::vector<double>>(MyX, MyY);
    //Test.find_coefficients();
}
