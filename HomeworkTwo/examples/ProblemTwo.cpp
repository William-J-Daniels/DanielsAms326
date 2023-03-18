// my libraries
#include <midpoint.h>
// cpp libraries
#include <iostream>
#include <cmath>
#include <limits>

/* Since I wrote the integrator to work only in one dimension, I would either
 * need a separate function for each Airy, or to use a global variable. I choose
 * to use the global variable.
 */

double x;
double Airy(double input);

int main()
{
    x = -3.0;
    auto Airyn3 = intgrt::Midpoint(Airy);
    std::cout << "With x=-3, I get "
              << Airyn3.converge(0.0, 25.0, 128, std::numeric_limits<unsigned>::max())/M_PI
              << std::endl;

    x = -2.0;
    auto Airyn2 = intgrt::Midpoint(Airy);
    std::cout << "With x=-2, I get "
              << Airyn2.converge(0.0, 25.0, 128, std::numeric_limits<unsigned>::max())/M_PI
              << std::endl;

    x = -1.0;
    auto Airyn1 = intgrt::Midpoint(Airy);
    std::cout << "With x=-1, I get "
              << Airyn1.converge(0.0, 25.0, 128, std::numeric_limits<unsigned>::max())/M_PI
              << std::endl;

    x = 0.0;
    auto Airy0 = intgrt::Midpoint(Airy);
    std::cout << "With x=0, I get "
              << Airy0.converge(0.0, 25.0, 128, std::numeric_limits<unsigned>::max())/M_PI
              << std::endl;

    x = 1.0;
    auto Airyp1 = intgrt::Midpoint(Airy);
    std::cout << "With x=1, I get "
              << Airyp1.converge(0.0, 25.0, 128, std::numeric_limits<unsigned>::max())/M_PI
              << std::endl;

    x = 2.0;
    auto Airyp2 = intgrt::Midpoint(Airy);
    std::cout << "With x=2, I get "
              << Airyp1.converge(0.0, 25.0, 128, std::numeric_limits<unsigned>::max())/M_PI
              << std::endl;

    x = 3.0;
    auto Airyp3 = intgrt::Midpoint(Airy);
    std::cout << "With x=3, I get "
              << Airyp3.converge(0.0, 25.0, 128, std::numeric_limits<unsigned>::max())/M_PI
              << std::endl;

    return 0;
}

double Airy(double input)
{
    return std::cos(std::pow(input, 3)/3.0 + x*input);
}

