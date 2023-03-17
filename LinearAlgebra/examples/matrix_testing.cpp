#include <matrix.h>
#include <iostream>

int main()
{
    // auto Test1 = la::Matrix<double>(std::pow(2, 10), std::pow(2, 10));
    // auto Test2 = la::Matrix<double>(std::pow(2, 10), std::pow(2, 10));
    //
    // Test1.rand(0.3, 0.305);
    // Test2.rand(0.333, 0.305);
    //
    // auto Test3 = Test1.naive_mult(Test2);

    auto Test = la::Matrix<double>(5,5);
    Test.rand(0.5,0.5127);

    std::cout << Test << std::endl;
    std::cout << Test(1,1) << " -> " << Test(3,3) << std::endl;
    std::cout << "begin loop" << std::endl;
    for (auto p = Test.slice_begin(1,1,2,2);  p != Test.slice_end(1,1,2,2); p++)
    {
        std::cout << *p << " ";// << std::endl;
    }

    for (auto p = Test.row_begin(); p != Test.row_end(); p++)
    {
        std::cout << *p << " ";
    }
    std::cout << std::endl;
    for (auto p = Test.column_begin(); p != Test.column_end(); p++)
    {
        std::cout << *p << " ";
    }
}
