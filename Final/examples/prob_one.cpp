/* Buffon's needle problem; F.1
 *
 * How it's done:
 * - The center of the needle can end up anywhere in a dxd box
 * - The angle of the needle can be any angle [0, 2pi)
 * - We simulate a needle being dropped as having a uniform distribution of
 *   positions and angles
 * - Via translational symmetry, it is sufficient to simulate a single box of
 *   size dxd and check if the needle contacts any of the edges
 */

// cpp17 libraries
#include <vector>
#include <cmath>
#include <iostream>

// my libraries
#include <uniformgenerator.h>

const int N = 1000000; // number of needles to drop
const double L = 1.0;  // length of the needle

int main()
{
    std::vector<double> ds = {1.0, 2.0, 3.0}; // sizes of grids to test
    std::vector<int> clear = {0, 0, 0}; // number of needles which don't touch
                                        // the grid. Corresponds to grid size of
                                        // the same index in ds

    #pragma omp parallel for
    for (int i = 0; i < ds.size(); i++)
    { // for each grid size
        auto numGen = rng::UniformGenerator<double>(0.375205, 0.376047);
        std::vector<double> position(3);

        for (int j = 0; j < N; j++)
        { // simulate N needles

            // drop a needle by generating random numbers
            position = {
                numGen() * ds[i],   // idx 0 is x pos [0, d)
                numGen() * ds[i],   // idx 1 is y pos [0, d)
                numGen() * 2.0*M_PI // idx 2 is polar angle [0, 2pi)
            };

            // check if the needle is in bounds by computing the extreames of
            // its position
            if (std::abs(position[0] + 0.5*L*std::cos(position[2])) < ds[i] && // x
                std::abs(position[0] - 0.5*L*std::cos(position[2])) < ds[i] &&
                std::abs(position[1] + 0.5*L*std::sin(position[2])) < ds[i] && // y
                std::abs(position[1] - 0.5*L*std::sin(position[2])) < ds[i])
                clear[i]++;
        }
    }

    std::cout << "Probabilites that the needle does not touch the wire:"
              << std::endl;
    for (auto& c : clear)
    {
        std::cout << c/static_cast<double>(N) << std::endl;
    }

    return 0;
}
