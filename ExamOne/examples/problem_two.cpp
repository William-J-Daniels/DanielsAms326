// my libraries
#include <bisection.h>
#include <newtonraphson.h>
#include <secant.h>
// cpp standard libraries
#include <cmath>
#include <iostream>

// function prototypes
double circle(double input);
double function(double input);

int main()
{
    auto MyBisection = roots::Bisection(function);
    auto MyNewton    = roots::NewtonRaphson(function);
    auto MySecant    = roots::Secant(function);

    std::cout << "The left root according to bisection is "
              << MyBisection.find_root(0.5, 4.5) << ". It took "
              << MyBisection.get_num_iter() << " iterations." << std::endl;

    std::cout << "The left root according to Newton-Raphson is "
              << MyNewton.find_root(0.5) << ". It took "
              << MyNewton.get_num_iter() << " iterations." << std::endl;

    std::cout << "The left root according to secant is "
              << MySecant.find_root(0.5, 4.5) << ". It took "
              << MySecant.get_num_iter() << " iterations." << std::endl;

    std::cout << "Since the left root and the right root just have different "
              << "signs, we conclude that the roots are -2 and 2." << std::endl;

    return 0;
}

// function definitions
double function(double input)
{
    return (
    (16.0 - 8.0 * input)
    /
    (16.0 + 4.0 * input)
    );
}
