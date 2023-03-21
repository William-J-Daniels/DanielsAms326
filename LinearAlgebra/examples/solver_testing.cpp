#include <linearsolver.h>
#include <iostream>

int main()
{
    la::Matrix<double> A{{{1,  1,  1},
                          {-1, 2,  0},
                          {2,  0,  1}}};
    std::vector<double> b{6, 3, 5};
    // la::Matrix<double> A{{{{1,  2,  3,  4},
    //                        {5,  1,  6, -1},
    //                        {10, 2, 13, -2},
    //                        {4, 10, -2, -5}}}};
    // std::vector<double> b{3,  2,  4,  1};
    // auto A = la::Matrix<double>(10, 10);
    // A.rand(0.01, 0.01);
    // std::vector<double> b(10);

    std::vector<double> init_guess{0,0,0};

    auto Sln = la::LinearSolver(A, b);

    //auto Results = Sln.gaus_elim();
    auto Results = Sln.jacobi_iter(init_guess);

    for (auto& R : Results)
        std::cout << R << " ";

    return 0;
}
