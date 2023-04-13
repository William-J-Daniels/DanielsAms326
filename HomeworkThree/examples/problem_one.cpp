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
    unsigned iter = 512;

    // gaussiam elimination
    auto Solver = la::LinearSolver(A, b);
    auto result = Solver.gaus_elim();
    std::cout << "Gaussian elimination solution:" << std::endl;
    for (auto& r : result)
        std::cout << r << " ";
    std::cout << std::endl << std::endl;

    // jacobi iteration
    Solver = la::LinearSolver(A, b);
    Solver.set_max_iter(iter);
    result = Solver.jacobi_iter(b);
    std::cout << "Jacobi iteration solution:" << std::endl;
    for (auto& r : result)
        std::cout << r << " ";
    std::cout << std::endl << std::endl;

    // gauss seidel method
    Solver = la::LinearSolver(A, b);
    Solver.set_max_iter(iter);
    result = Solver.gauss_seidel(b);
    std::cout << "Gauss-Seidel solution:" << std::endl;
    for (auto& r : result)
        std::cout << r << " ";
    std::cout << std::endl << std::endl;

    // SOR
    Solver = la::LinearSolver(A, b);
    Solver.set_max_iter(iter);
    result = Solver.SOR(b, 1.5);
    std::cout << "SOR:" << std::endl;
    for (auto& r : result)
        std::cout << r << " ";
    std::cout << std::endl << std::endl;

    return 0;
}
