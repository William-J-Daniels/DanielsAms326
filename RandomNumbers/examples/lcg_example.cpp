#include <iostream>
#include <lcg.h>

int main()
{
    rng::LCG generator;
    const int NUM_GENERATIONS = 10;

    for (int i = 0; i < NUM_GENERATIONS; i ++)
    {
        std::cout << generator() << std::endl;
    }

    return 0;
}
