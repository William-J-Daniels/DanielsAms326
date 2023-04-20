#include <ieuler.h>

#include <vector>
#include <fstream>

int main()
{
    std::vector<double> Results (200000);
    double delta = 1.0e-4, x, y = -1.0;
    for (unsigned i = 0; i < 100000; i++)
    {
        x = delta * i;

        auto DE = [=] (double input) {
            return input + std::log(input + x*x + y*y);
        };

        auto Ode = ode::iEuler(DE, x, y, delta);
        y = Ode.advance(delta);

        Results[2*i] = x;
        Results[2*i + 1] = y;
    }

    std::string Filename = "../../OrdinaryDifferentialEquations/data/implicit_test.csv";
    std::ofstream Outfile(Filename);
    if (Outfile.fail())
    { // should we fail to open the file for any reason
        // give and error, exit program
        std::cerr << "Failed to open " << Filename << ". Check that you have "
                  << "the necessary permisions and that the path exists."
                  << std::endl;
        std::exit(EXIT_FAILURE);
    }
    // first write a header to the file
    Outfile << "x,y" << std::endl;
    for (unsigned i = 0; i < 10000; i++)
    {
        Outfile << Results[2*i] << "," << Results[2*i + 1] << std::endl;
    }
    Outfile.close();

    return 0;
}
