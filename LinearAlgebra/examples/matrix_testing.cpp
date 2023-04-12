#include <matrix.h>
#include <iostream>

int main()
{
    auto Test1 = la::Matrix<double>(std::pow(2, 12), std::pow(2, 12));
    auto Test2 = la::Matrix<double>(std::pow(2, 12), std::pow(2, 12));

    Test1.rand(0.3, 0.305);
    Test2.rand(0.333, 0.305);

    auto Test3 = Test1.naive_mult(Test2);

    // auto A = la::Matrix<double>(4, 10);
    // A.rand(3.333, 3.321);
    //
    // std::cout << A << std::endl;
    // A.transpose();
    // A.transpose();
    // std::cout << A << std::endl;
}
