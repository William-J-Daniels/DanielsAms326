#ifndef UNIFORMGENERATOR_H
#define UNIFORMGENERATOR_H

#include <cmath>
#include <cstdlib>
#include <iostream>

namespace rng {

template <class T>
class UniformGenerator // implimentation of the generator from the notes
{                      // uniform distribution on (0.0, 1.0)
public:
    // can construct with default seeds or with custom seeds
    UniformGenerator() = default;
    UniformGenerator(T current_seed, T previous_seed);

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
    double current_state  = 0.375205, // values from notes
           previous_state = 0.376047;
};

} // namespace rng

using namespace rng;

template <class T>
UniformGenerator<T>::UniformGenerator(T current_seed, T previous_seed)
{
    /*
     * Destructor wich sets the seeds to a custom value.
     * Neither value, nor their sums, may be equal to 0.0 or 1.0
     */

    current_state  = current_seed;
    previous_state = previous_seed;
}

template <class T>
T rng::UniformGenerator<T>::operator() ()
{
    /*
     * Advance state and return the current state.
     *
     * Uses cmath.
     */

    current_state = fmod(current_state + previous_state, 1.0);
    return current_state;
}

template <class T>
void rng::UniformGenerator<T>::discard()
{
    /*
     * Advance state and do not return the state.
     */

    current_state = fmod(current_state + previous_state, 1.0);
}

template <class T>
void rng::UniformGenerator<T>::seed(T new_current_state, T new_previous_state)
{
    /*
     * Set the state. Check that the current, previous, and sum of states are
     * not equal to zero or one.
     */

    if (new_current_state  == 1 ||
        new_previous_state == 1 ||
        new_current_state + new_previous_state == 1)
    {
        std::cerr << "The seeds " << new_current_state << " and "
                  << new_previous_state << "provided are not appropriate since "
                  << "one of them or their sum is equal to zero. Exiting "
                  << "program.";
        std::exit(EXIT_FAILURE);
    }

    current_state  = new_current_state;
    previous_state = new_previous_state;
}

template <class T>
T rng::UniformGenerator<T>::max()
{
    /*
     * Returns the maximal value returned by the generator.
     */

    return 1.0;
}

template <class T>
T rng::UniformGenerator<T>::min()
{
    /*
     * Returns the minimal value returned by the operator.
     */

    return 0.0;
}

#endif // UNIFORMGENERATOR_H
