#include <prob_two.h>

#include <vector>
#include <iostream>


const unsigned NUM_X = 512;
const unsigned RNG_POINTS = std::pow(2, 18);
const double MIN_ROT = 0.0;
const double MAX_ROT = 0.5*M_PI;
const double MIN_X = -1.0;
const double MAX_X =  1.0;
const double MIN_Y = -2.0;
const double MAX_Y =  1.0;
const unsigned NUM_TRANS = 1024;


int main()
{
    // variables to hold result
    double max_overlap = 0.0;
    std::array<double, 3> max_state;

    // set up all the transformations
    std::array<std::vector<double>, 3> transformations {
        std::vector<double> (NUM_TRANS),
        std::vector<double> (NUM_TRANS),
        std::vector<double> (NUM_TRANS)
    };
    #pragma omp parallel
    {
    #pragma omp for
    for (unsigned i = 0; i < NUM_TRANS; i++)
    {
        transformations[0][i] = i * (NUM_TRANS+1) *
                                (MAX_ROT - MIN_ROT) / (NUM_TRANS*NUM_TRANS) +
                                MIN_ROT;
    }
    #pragma omp for
    for (unsigned i = 0; i < NUM_TRANS; i++)
    {
        transformations[1][i] = i *(NUM_TRANS+1)*
                                (MAX_X - MIN_X) / (NUM_TRANS*NUM_TRANS) +
                                MIN_X;
    }
    #pragma omp for
    for (unsigned i = 0; i < NUM_TRANS; i++)
    {
        transformations[2][i] = i *(NUM_TRANS+1)*
                                (MAX_Y - MIN_Y) / (NUM_TRANS*NUM_TRANS) +
                                MIN_Y;
    }
    } // pragma omp parallel

    // iterate over the transformations and pick the maximum one
    for (auto& t : transformations[0])
    {
        for (auto& x : transformations[1])
        {
            for (auto& y : transformations[2])
            {
                auto heart    = hw3::make_heart(NUM_X, x, y);
                auto samples  = hw3::make_samples(RNG_POINTS, x, y);
                auto in_heart = hw3::heart_samples(samples, heart);

                auto quad    = hw3::make_quad(NUM_X, t);
                auto overlap = hw3::find_overlap(in_heart, quad);

                std::cout << t<< " " << x << " " << y << " " << overlap;
                if (overlap > max_overlap)
                {
                    max_overlap = overlap;
                    max_state = {t, x, y};
                    std::cout << "New max!";
                }
                std::cout << std::endl;
            }
        }
    }


    return 0;
}
