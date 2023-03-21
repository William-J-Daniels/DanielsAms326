#include <linearsolver.h>
#include <iostream>

int main()
{
    la::Matrix<double> A{{{1,  1,  1},
                          {-1, 2,  0},
                          {2,  0,  1}}};
    std::vector<double> b{6, 3, 5};
    // auto A = la::Matrix<double>(10, 10);
    // A.rand(0.01, 0.01);
    // std::vector<double> b(10);

    auto Sln = la::LinearSolver(A, b);

    std::cout << A << std::endl;
    Sln.gaus_elim();

    return 0;

    return 0;
}
