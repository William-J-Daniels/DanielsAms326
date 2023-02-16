#ifndef RNG_LCG_H
#define RNG_LCG_H

namespace rng {

class LCG // Linear Congruential Generator
{         // imitates std::minstd_rand
public:
    // can construct with a default seed (1) or with a custom seed
    LCG() = default;
    LCG(unsigned int init_seed);

    // advances the current state and returns it
    int operator() ();
    // advance state without returning the current state
    void discard();
    // set the state
    void seed(unsigned int new_seed);

    // return the max and min value of the generator
    static int max();
    static int min();

private:
    /* A computation involving unsigned operands can never overﬂow, because a
     * result that cannot be represented by the resulting unsigned integer type
     * is reduced modulo the number that is one greater than the largest value
     * that can be represented by the resulting type.
     *
     * From cpp specification
     */
    static constexpr unsigned int modulus    = 2147483647, // 2^31 - 1
                                  multiplier = 48271;      // prime number
    // increment not stored sice it is zero

    unsigned int state = 1; // default seed of 1

};

} // namespace rng

#endif // RNG_LCG_H
