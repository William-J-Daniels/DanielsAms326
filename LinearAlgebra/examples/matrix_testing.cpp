#include <matrix.h>
#include <iostream>

int main()
{
    auto Test1 = la::Matrix<double>(std::pow(2, 12), std::pow(2, 12));
    auto Test2 = la::Matrix<double>(std::pow(2, 12), std::pow(2, 12));

    Test1.rand(0.3, 0.305);
    Test2.rand(0.333, 0.305);

    auto Test3 = Test1 * Test2;
}
