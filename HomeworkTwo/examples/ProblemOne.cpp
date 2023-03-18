// my libraries
# include <matrix.h>
// cpp libraries
#include <iostream>

int main()
{
    auto A = la::Matrix<double>(std::pow(2, 10), std::pow(2, 10)),
         B = la::Matrix<double>(std::pow(2, 10), std::pow(2, 10));
    auto C = la::Matrix<double>(std::pow(2, 12), std::pow(2, 12)),
         D = la::Matrix<double>(std::pow(2, 12), std::pow(2, 12));

    auto E = A.naive_mult(B);
    auto F = A * B; // operator * overload is strassen method

    auto G = C.naive_mult(D);
    auto H = C * D;

    return 0;
}
