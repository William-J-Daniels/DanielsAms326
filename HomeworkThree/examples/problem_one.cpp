#include <matrix.h>
#include <linearsolver.h>

#include <iostream>


int main()
{
    la::Matrix<double> A{{{4, -1,  0, -1,  0,  0,  0,  0,  0},
                          {-1, 4, -1,  0, -1,  0,  0,  0,  0},
                          {0, -1,  4,  0,  0, -1,  0,  0,  0},
                          {-1, 0,  0,  4, -1,  0, -1,  0,  0},
                          {0, -1,  0, -1,  4, -1,  0, -1,  0},
                          {0,  0, -1,  0, -1,  4,  0,  0, -1},
                          {0,  0,  0, -1,  0,  0,  4, -1,  0},
                          {0,  0,  0,  0, -1,  0, -1,  4, -1},
                          {0,  0,  0,  0,  0, -1,  0, -1,  4}}};
    std::vector<double> b = {1, 1, 1, 1, 1, 1, 1, 1, 1};

    // gaussiam elimination
    auto Solver = la::LinearSolver(A, b);
    auto result = Solver.gaus_elim();
    std::cout << "Gaussian elimination solution:" << std::endl;
    for (auto& r : result)
        std::cout << r << " ";
    std::cout << std::endl;

    // jacobi iteration
    Solver = la::LinearSolver(A, b);
    result = Solver.jacobi_iter(b);
    for (auto& r : result)
        std::cout << r << " ";
    std::cout << std::endl;

    return 0;
}
