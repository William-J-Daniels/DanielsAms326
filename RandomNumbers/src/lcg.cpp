#include <lcg.h>

using namespace rng;

LCG::LCG(unsigned int init_seed)
{
    /*
     * Sets the seed
     */

    state = init_seed;
}

int LCG::operator() ()
{
    /*
     * Advances the current state and returns it
     */

    state = (multiplier * state) % modulus;
    return state;
}

void LCG::discard()
{
    /*
     * Advances the current state without returning anything
     */

    state = (multiplier * state) % modulus;
}

void rng::LCG::seed(unsigned int new_seed)
{
    /*
     * Sets the current state to new_seed
     */

    state = new_seed;
}


int LCG::max()
{
    /*
     * Returns the maximum possible value for the generator
     */

    return modulus;
}

int LCG::min()
{
    /*
     * Returns the minimum possible value for the generator
     */

    return 0;
}
