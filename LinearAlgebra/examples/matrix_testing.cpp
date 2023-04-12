#include <matrix.h>
#include <iostream>

int main()
{
    la::DiagonalMatrix<double> A{{1, 2, 3, 4}};
    std::vector<double> b{1, 2, 3, 4};

    auto c = A*b;

    for (auto& elem : c)
        std::cout << elem << " ";
}
