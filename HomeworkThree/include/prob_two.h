#ifndef HW3_PROBTHREE
#define HW3_PROBTHREE

#include <vector>
#include <array>
#include <cassert>
#include <algorithm>
#include <execution>
#include <cmath>
#include <fstream>
#include <iostream>

namespace hw3 {

std::array<std::vector<double>, 3> make_heart(unsigned num_points)
{
    /* Creates and returns an array of vectors containing the upper and lower
     * halves of the heart. Also writes csv file so it can be plotted with
     * pandas and matplotlib
     */
    assert(num_points > 0);
    assert(!(num_points%2));

    std::vector<double> x_vals (num_points);
    std::vector<double> top (num_points);
    std::vector<double> bottom (num_points);

    #pragma omp parallel for
    for (std::size_t i = 0; i < num_points; i++)
    {
        x_vals[i] = -0.5 * std::sqrt(2.0) +
                    (i*std::sqrt(2.0)*(num_points+1)) / (num_points*num_points);
    }

    // #pragma omp parallel for
    for (std::size_t i = num_points/2; i < num_points; i++)
    {
        top[i]    = std::pow(x_vals[i], 2.0/3.0) +
                    0.5 * std::sqrt(2.0 - 4.0 * x_vals[i]*x_vals[i]);
        bottom[i] = std::pow(x_vals[i], 2.0/3.0) -
                    0.5 * std::sqrt(2.0 - 4.0 * x_vals[i]*x_vals[i]);
        top[num_points-1-i]    = top[i];
        bottom[num_points-1-i] = bottom[i];
    }

    std::string Filename = "../../HomeworkThree/data/heart.csv";
    std::ofstream Outfile(Filename);
    if(Outfile.fail())
    {
        std::cerr << "Could not open " << Filename << std::endl;
        std::exit(EXIT_FAILURE);
    }
    Outfile << "x,y" << std::endl;
    for (std::size_t i = 0; i < x_vals.size(); i++)
    {
        Outfile << x_vals[i] << "," << top[i] << std::endl;
        std::cout << i << std::endl;
    }
    for (int i = x_vals.size()-1; i >= 0; i--)
    {
        Outfile << x_vals[i] << "," << bottom[i] << std::endl;
    }
    Outfile.close();

    return std::array<std::vector<double>, 3> {x_vals, top, bottom};
}

} // namespace hw3

#endif // HW3_PROBTHREE
