// my libraries
#include <simpson.h>
#include <midpoint.h>
#include <trapezoid.h>

// cpp libraries
#include <iostream>
#include <cmath>
#include <limits>

/* I wrote my integration classes to operate on only one dimension, so in order
 * to integrate the Airy function which depends on both x and t, I would either
 * need to write separate airy function functions or use a global variable.
 * Since having many functions is unaesthetic, I choose to use the global
 * variable even though it is generally bad practice.
 */
double x;

// airy function definition
double Airy(double t)
{
    // integrand of Airy function
    return std::cos(std::pow(t, 3)/3.0 + x*t) / M_PI;
}

int main()
{
    // integration objects
    auto Simp = intgrt::Simpson  (Airy);
    auto Mid  = intgrt::Midpoint (Airy);
    auto Trap = intgrt::Trapezoid(Airy);
    unsigned num_iter = std::pow(2, 20);

    for (int i = -3; i <= 3; i++)
    {
        x = static_cast<double>(i);
        std::cout << "Approximations for Simpson, midpoint, and trapezoid when "
                  << " x = " << x << std::endl;
        // my age is 21, so that is my approximation for infinity
        std::cout << Simp.evaluate(0.0, 21.0, num_iter) << std::endl
                  << Mid. evaluate(0.0, 21.0, num_iter) << std::endl
                  << Trap.evaluate(0.0, 21.0, num_iter) << std::endl
                  << std::endl;
    }

    return 0;
}
