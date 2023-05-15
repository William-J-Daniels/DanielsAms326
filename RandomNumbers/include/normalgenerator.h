#ifndef NORMALGENERATOR_H
#define NORMALGENERATOR_H

#include <cmath>
// #include <
#include "uniformgenerator.h"

namespace rng {

template <class T>
class NormalGenerator
{
public:
    // can construct with default seeds or with custom seeds
    NormalGenerator() = default;
    NormalGenerator(T current_seed, T previous_seed);

    // advances the current state and returns it
    T operator() ();
    // advance state without returning the current state
    void discard();
    // set the state
    void seed(T new_current_state, T new_previous_state);

    // return the max and min of the generator
    static T max();
    static T min();

private:
    UniformGenerator<T> Ugen();
    double num1, num2;

    double mean = 0.0, variance = 0.5;

};

} // namespace rng

using namespace rng;

template <class T>
T rng::NormalGenerator<T>::operator() ()
{
    num1 = Ugen(); num2 = Ugen();
    double g1 = std::sqrt(-2.0 * std::log(num1)) * std::cos(2.0*M_PI * num2);
    double g2 = std::sqrt(-2.0 * std::log(num1)) * std::sin(2.0*M_PI * num2);
}

#endif // NORMALGENERATOR_H
