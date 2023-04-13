#include <matrix.h>
#include <iostream>

int main()
{
    auto A = la::Matrix<double> (10, 10);
    A.rand(0.334, 0.3347);
    std::cout << A <<std::endl;

    auto v = A.diag();
    for (auto& vee : v)
        std::cout << vee << " ";
    std::cout << std::endl << std::endl;

    auto D = la::DiagonalMatrix<double> {v};

    std::cout << A - D;
}
