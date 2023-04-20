#include <matrix.h>
#include <iostream>

int main()
{
     auto C = la::Matrix<double>(std::pow(2, 10), std::pow(2, 10)),
          D = la::Matrix<double>(std::pow(2, 10), std::pow(2, 10));

    C.naive_mult(D);
}
