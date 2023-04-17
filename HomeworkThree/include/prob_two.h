#ifndef HW3_PROBTHREE
#define HW3_PROBTHREE

#include <uniformgenerator.h>
#include <improved_sort.h>

#include <vector>
#include <array>
#include <cassert>
#include <algorithm>
#include <execution>
#include <cmath>
#include <fstream>
#include <iostream>

namespace hw3 {

std::array<std::vector<double>, 3> make_heart(unsigned num_points,
                                              double x_trans, double y_trans)
{
    /* Creates and returns an array of vectors containing the upper and lower
     * halves of the heart. Also writes csv file so it can be plotted with
     * pandas and matplotlib
     */
    assert(num_points > 0);
    assert(!(num_points%2)); // take advantage of symmetry

    std::vector<double> x_vals (num_points);
    std::vector<double> top (num_points);
    std::vector<double> bottom (num_points);

    #pragma omp parallel
    {
    #pragma omp for
    for (std::size_t i = 0; i < num_points; i++)
    {
        x_vals[i] = -0.5 * std::sqrt(2.0) +
                    (i*std::sqrt(2.0)*(num_points+1)) / (num_points*num_points);
    }
    #pragma omp for
    for (std::size_t i = num_points/2; i < num_points; i++)
    {
        top[i]    = std::pow(x_vals[i], 2.0/3.0) +
                    0.5 * std::sqrt(2.0 - 4.0 * x_vals[i]*x_vals[i])
                    + y_trans;
        bottom[i] = std::pow(x_vals[i], 2.0/3.0) -
                    0.5 * std::sqrt(2.0 - 4.0 * x_vals[i]*x_vals[i])
                    + y_trans;
        top[num_points-1-i]    = top[i];
        bottom[num_points-1-i] = bottom[i];
    }
    #pragma omp for
    for(std::size_t i = 0; i < num_points; i++)
    {
        x_vals[i] = x_vals[i] + x_trans;
    }
    } // pragma omp parallel

    return std::array<std::vector<double>, 3> {x_vals, top, bottom};
}

void heart_csv(std::array<std::vector<double>, 3> heart)
{
    std::string Filename = "../../HomeworkThree/data/heart.csv";
    std::ofstream Outfile(Filename);
    if(Outfile.fail())
    {
        std::cerr << "Could not open " << Filename << std::endl;
        std::exit(EXIT_FAILURE);
    }
    Outfile << "x,y" << std::endl;
    for (std::size_t i = 0; i < heart[0].size(); i++)
    {
        Outfile << heart[0][i] << "," << heart[1][i] << std::endl;
    }
    for (int i = heart[0].size()-1; i >= 0; i--)
    {
        Outfile << heart[0][i] << "," << heart[2][i] << std::endl;
    }
    Outfile.close();
}

std::array<std::vector<double>, 2> make_quad(unsigned num_points, double rot)
{
    /* Creates and returns an array of vectors containing the x and y
     * coordinates, num_points evenly spaced, of the quadrifolium. Also accepts
     * parameters for transformations. First makes vectors in polar coordinates,
     * where it is advantageous to apply the rotation, then converts to
     * cartesian, where it is easy to translate and plot. Writes data in csv
     * format in cartesian
     */
    assert(num_points > 0);

    std::vector<double> theta  (num_points);
    std::vector<double> r_vals (num_points);
    std::vector<double> x_vals (num_points);
    std::vector<double> y_vals (num_points);

    #pragma omp parallel for
    for (std::size_t i = 0; i < num_points; i++)
    {
        theta[i]  = (i * 2.0*M_PI * (num_points+1)) / (num_points * num_points);
        r_vals[i] = std::sin(2.0*theta[i] + rot);
    }

    return std::array<std::vector<double>, 2> {theta, r_vals};
}

void quad_csv(std::array<std::vector<double>, 2> quad)
{
    std::string Filename = "../../HomeworkThree/data/quad.csv";
    std::ofstream Outfile(Filename);
    if(Outfile.fail())
    {
        std::cerr << "Could not open " << Filename << std::endl;
        std::exit(EXIT_FAILURE);
    }
    Outfile << "x,y" << std::endl;
    for (std::size_t i = 0; i < quad[0].size(); i++)
    {
        Outfile << quad[1][i] * std::cos(quad[0][i]) << ","
                << quad[1][i] * std::sin(quad[0][i]) << std::endl;
    }
    Outfile.close();
}

std::array<std::vector<double>, 2> make_samples(unsigned sample_res,
                                                double x_trans, double y_trans)
{
    /* Generate random samples once here because I only know how to code up a
     * prng, so there's no point in running it again every time we calculate the
     * overlap even though in principle we should
     */

    std::array<rng::UniformGenerator<double>, 2> rng {
        rng::UniformGenerator<double>(0.232556, 0.535463),
        rng::UniformGenerator<double>(0.375205, 0.257654)
    };
    std::array<std::vector<double>, 2> samples {
        std::vector<double> (sample_res),
        std::vector<double> (sample_res)
    };
    for (unsigned i = 0; i < sample_res; i++)
    { // can't parallelize-- output of rng has markov property
        samples[0][i] = rng[0]() * 1.5 - 0.75 + x_trans;
        samples[1][i] = rng[1]() * 2.0 - 0.75 + y_trans;
    }

    return samples;
}

std::array<std::vector<double>, 2> heart_samples(
    const std::array<std::vector<double>, 2>& samples,
    const std::array<std::vector<double>, 3>& heart)
{
    /* Again taking advantage of the fact that we're stuck with prng, since I
     * will only transform the quadrifolium (taking advantage of its symmetry),
     * I only have to find the samples within the heart once. We return these
     * samples in polar coordinates to make comparing to the quadrifolium easier
     */

    std::array<std::vector<double>, 2> in_heart {
        std::vector<double>(samples[0].size()),
        std::vector<double>(samples[0].size())
    };
    unsigned hits = 0;
    for (unsigned i = 0; i < samples[0].size(); i++)
    {
        // check if x val lies within the heart
        if (samples[0][i] >= heart[0][0] && samples[0][i] <= heart[0].back())
        { // cant parallelize without needing significant serial processing of
          // the resulting vectors-- not worth it
            // check if y val also lies within the heart w/ linear interpolation
            auto heart_ptr = std::lower_bound(
                heart[0].begin(), heart[0].end(), samples[0][i]
            );
            unsigned h_idx = std::distance(heart[0].begin(), heart_ptr);
            double heart_interp_hi = heart[1][h_idx] +
                                     (heart[0][h_idx] - samples[0][i]) *
                                     (heart[1][h_idx+1] - heart[1][h_idx]) /
                                     (heart[0][h_idx+1] - heart[0][h_idx]);
            double heart_interp_lo = heart[2][h_idx] +
                                     (heart[0][h_idx] - samples[0][i]) *
                                     (heart[2][h_idx+1] - heart[2][h_idx]) /
                                     (heart[0][h_idx+1] - heart[0][h_idx]);
            if (samples[1][i] > heart_interp_lo &&
                samples[1][i] < heart_interp_hi)
            {
                // add to hits vector
                in_heart[0][hits] = std::atan2(samples[1][i], samples[0][i]);
                if (in_heart[0][hits] < 0.0)
                    in_heart[0][hits] = in_heart[0][i] + 2.0*M_PI;
                in_heart[1][hits] = std::sqrt(samples[0][i]*samples[0][i] +
                                           samples[1][i]*samples[1][i]);
                hits++;
            }
        }
    }
    in_heart[0].resize(hits); in_heart[1].resize(hits);
    std::sort(
        sort_it{0,                  in_heart[0].data(), in_heart[1].data()},
        sort_it{in_heart[0].size(), in_heart[0].data(), in_heart[1].data()}
    );

    return in_heart;
}

double find_overlap(const std::array<std::vector<double>, 2>& samples,
                    const std::array<std::vector<double>, 2>& quad)
{
    /* Uses Monte Carlo importance sampling to estimate the area of overlap
     */

    unsigned hits = 0;
    #pragma omp parallel reduction (+:hits)
    {
    #pragma omp for
    for (unsigned i = 0; i < samples[0].size(); i++)
    {
        // accept sample if r_samples <= r_quad, interpolate linearly for r_quad
        auto quad_ptr = lower_bound(
            quad[0].begin(), quad[0].end(), samples[0][i]
        );
        unsigned q_idx = std::distance(quad[0].begin(), quad_ptr);
        double r_interp = quad[1][q_idx] + (quad[0][q_idx] - samples[0][i]) *
                          (quad[1][q_idx+1]-quad[1][q_idx]) /
                          (quad[0][q_idx+1]-quad[0][q_idx]);
        if (samples[1][i] <= r_interp)
            hits++;
    }
    } // pragma omp parallel reduction (+:hits)
    return M_PI/2.0 * hits / samples[0].size();
}

} // namespace hw3

#endif // HW3_PROBTHREE
