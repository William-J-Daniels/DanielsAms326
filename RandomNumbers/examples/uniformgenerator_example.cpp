#include <iostream>
#include <vector>
#include <fstream>

#include <uniformgenerator.h>

const unsigned NUM_POINTS = 8192;

int main()
{
    std::vector<float> points (2*NUM_POINTS);
    auto gen1 = rng::UniformGenerator<float>(0.232556, 0.535463);
    auto gen2 = rng::UniformGenerator<float>(0.375205, 0.257654);
    for (unsigned i = 0; i < NUM_POINTS; i+=2)
    {
        points[i]   = gen1()*10.0;
        points[i+1] = gen2();
    }

    std::string Filename = "../../RandomNumbers/data/uniform_points.csv";
    std::ofstream Outfile(Filename);
    if (Outfile.fail())
        std::exit(EXIT_FAILURE);
    Outfile << "x,y" << std::endl;
    for (unsigned i = 0; i < NUM_POINTS; i+=2)
        Outfile << points[i] << "," << points[i+1] << std::endl;
    Outfile.close();

    return 0;
}
