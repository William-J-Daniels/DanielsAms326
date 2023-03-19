#include <iostream>
#include <uniformgenerator.h>

int main()
{
    rng::UniformGenerator<double> generator;
    const int NUM_GENERATIONS = 30;

    for (int i = 0; i < NUM_GENERATIONS; i ++)
    {
        std::cout << generator() * (5.0 - 3.0) + 3.0 << std::endl;
    }

    return 0;
}
