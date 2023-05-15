/* Trading; F2
 *
 * Idea:
 * - s(0) = 1.0 (million)
 * - Apply the specified equations, thats about it
 */

// cpp17 libs
#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>

// my libs

// functions
double gauss(double x, double mu, double sigma)
{
    return(
        std::pow(2.0*M_PI*sigma*sigma, -0.5) *
        std::exp((x-mu)*(x-mu) / (-2.0*sigma*sigma))
    );
}

int main()
{
    std::vector<std::vector<double>> params = {{-0.0019, 0.0084},
                                               { 0.0008, 0.0018}};
    // ^^^ vector for the specified means and variances
    std::vector<std::vector<double>> results = {
        std::vector<double>(260),
        std::vector<double>(260)
    };
    // ^^^ vector of vectors to store the results. Units in millions
    results[0][0] = 1000000.0;
    results[1][0] = 1000000.0;
    // ^^^ initialize the investment

    for (int i = 0; i < params.size(); i++)
    {
        double x = 0.0001, prev_x;
        for (int j = 0; j < 260; j++)
        {
            prev_x = x;
            x = gauss(prev_x, params[i][0], params[i][1]);
            if (x > 0)
                results[i][j] *= (1.0 + x/100.0) * 0.9334;
            else
                results[i][j] *= 1.0 + x;

            std::cout << prev_x << ", " << x << std::endl;
        }
    }

    // write results to csv
    std::string Filename = "../../Final/data/F2.csv";
    std::ofstream OptFile(Filename);
    OptFile << "a,b" << std::endl;
    for (unsigned i = 0; i < results[0].size(); i++)
        OptFile << results[0][i] << "," << results[1][i] << std::endl;
    OptFile.close();

    return 0;
}
