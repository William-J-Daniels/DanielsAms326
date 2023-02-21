#include <matrix.h>
#include <iostream>

int main()
{
    auto Test1 = la::Matrix<double>(3, 3, 5.0);
    auto Test2 = la::Matrix<double>(3, 3, 1.0);

    //Test1.set(1,1,0);
    std::cout << Test1 << std::endl;
    std::cout << Test1*10.0 << std::endl;

}
