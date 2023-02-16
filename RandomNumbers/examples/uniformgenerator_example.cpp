#include <iostream>
#include <uniformgenerator.h>

int main()
{
    rng::UniformGenerator<double> generator;
    const int NUM_GENERATIONS = 10;

    for (int i = 0; i < NUM_GENERATIONS; i ++)
    {
        std::cout << generator() << std::endl;
    }

    return 0;
}
