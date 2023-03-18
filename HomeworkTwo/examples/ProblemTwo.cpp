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

double t;
double Airy(double input);

int main()
{
    t = -3.0;
    auto Airyn3 = intgrt::Midpoint(Airy);
    std::cout << "With t=-3, I get "
              << Airyn3.converge(
                  0.0, 25.0, 512, std::numeric_limits<unsigned>::max()
              )/M_PI
              << std::endl;
    return 0;
}

double Airy(double input)
{
    return std::cos(std::pow(t, 3)/3.0 + input*t);
}

