// my libraries
#include <euler.h>
#include <eulercromer.h>
#include <midpoint.h>
#include <huen.h>

// cpp standard libraries
#include <vector>
#include <iostream>
#include <cmath>
#include <execution>
#include <list>
#include <array>
#include <string>
#include <fstream>

// constants
const unsigned RES = 1024; // resolution of search grid
const double MIN_ANG = -1.4; // angle search space
const double MAX_ANG =  1.4;
const double STEP = 1.0e-4; // set size in miles
// easier to read than magic numbers
const double a = 8.0;
const double v0 = 20.0, vb = 30.0;

int main()
{
    // make search space
    std::vector<double> betas (RES);
    std::vector<double> results (RES);

    // populate search vector
    #pragma omp parallel for
    for (unsigned i = 0; i < RES; i++)
        betas[i] = i * (RES+1) * (MAX_ANG - MIN_ANG) / (RES*RES) + MIN_ANG;

    // brute force search for the optimal path
    #pragma omp parallel for
    for (unsigned i = 0; i < RES; i++)
    {
        double d_travel = 0.0;
        auto DE = [=] (double x) {
            return (v0 / vb) * (1.0 - ((x*x)/(a*a))) / std::cos(betas[i]) +
                   std::tan(betas[i]);
        };
        auto Int = ode::Midpoint(DE, -a, 0, STEP);
        while (Int.get_x() < a)
        {
            auto prev_y = Int.get_y();
            Int.advance(STEP);
            d_travel += std::sqrt(
                STEP*STEP + (prev_y-Int.get_y())*(prev_y-Int.get_y())
            );
        }
        results[i] = d_travel;
    }

    // find the minimum travel and angle
    auto min = std::min_element(
        std::execution::par, results.begin(), results.end()
    );
    auto min_idx = std::distance(results.begin(), min);

    // create list for a plot
    std::list<std::array<double, 2>> plot;

    auto DE = [=] (double x) {
        return (v0 / vb) * (1.0 - ((x*x)/(a*a))) / std::cos(betas[min_idx]) +
               std::tan(betas[min_idx]);
    };
    auto Int = ode::Midpoint(DE, -a, 0, STEP);
    while (Int.get_x() < a)
    {
        Int.advance(STEP);
        plot.push_back({Int.get_x(), Int.get_y()});
    }

    // write csv files to be used with python for plots
    std::string OptFilename = "../../ExamThree/data/travel.csv";
    std::ofstream OptFile(OptFilename);
    OptFile << "beta,d_travel" << std::endl;
    for (unsigned i = 0; i < RES; i++)
        OptFile << betas[i] << "," << results[i] << std::endl;
    OptFile.close();

    std::string PathFilename = "../../ExamThree/data/shortest.csv";
    std::ofstream PathFile(PathFilename);
    PathFile << "x,y" << std::endl;
    for (auto& c : plot)
        PathFile << c[0] << "," << c[1] << std::endl;
    PathFile.close();

    std::cout << "The optimal angle is " << betas[min_idx] << ", producing a"
              << " distance traved of " << *min << std::endl;

    return 0;
}
