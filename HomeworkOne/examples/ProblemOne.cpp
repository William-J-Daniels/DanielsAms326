// my libraries
#include <bisection.h>
#include <newtonraphson.h>
#include <secant.h>
#include <fixedpoint.h>
// cpp libraries
#include <cmath>
#include <iostream>

// function prototypes-- definitions after main
double Function     (double input);
double Derivative   (double input);
double Tranformation(double input);

int main()
{
    // variables and objects
    auto Bisection     = roots::Bisection(Function);
    auto NewtonRaphson = roots::NewtonRaphson(Function, Derivative);
    auto Secant        = roots::Secant(Function);
    auto FixedPoint    = roots::FixedPoint(Tranformation);

    // call find_root for each objects
    std::cout << "The root according to bisection is "
              << Bisection.find_root(0.0, 1.0) << ". It took "
              << Bisection.get_num_iter() << " iterations." << std::endl;

    std::cout << "The root according to Newton-Raphson is "
              << NewtonRaphson.find_root(0.3) << ". It took "
              << NewtonRaphson.get_num_iter() << " iterations." << std::endl;

    std::cout << "The root according to secant is "
              << Secant.find_root(0.0, 1.0) << ". It took "
              << Secant.get_num_iter() << " iterations." << std::endl;

    std::cout << "The root according to fixed point is "
              << FixedPoint.find_root(0.0) << ". It took "
              << FixedPoint.get_num_iter() << " iterations." << std::endl;

    return 0;
}

double Function(double input)
{
    return(
        std::cos(input) - std::pow(input, 3)
    );
}

double Derivative(double input)
{
    return(
        -(std::sin(input) + 3.0*std::pow(input, 2))
    );
}

double Tranformation(double input)
{
    return(
        (std::cos(input) + 2.0 * std::pow(input, 3))
        /
        (1.0 + 3.0 * std::pow(input, 2))
    );
}

