#ifndef LA_LINEARSOLVER_H
#define LA_LINEARSOLVER_H

#include <matrix.h>
#include <vector>
#include <cassert>
#include <thread>
#include <algorithm>
#include <cmath>

#include <iostream>

namespace la {

template <class T>
class LinearSolver
{
    // solves linear systems of the form  Ax=b for x
    // takes a reference to the data, if you need the original make a copy
public:
    LinearSolver() = default;
    LinearSolver(Matrix<T>& init_A, std::vector<T> init_b);

    std::vector<T> gaus_elim();

private:
    Matrix<T> A;
    std::vector<T> b;

    unsigned num_pivots = 0;

    std::vector<T> find_scales();
    void find_scales_helper(unsigned start, unsigned end,
                            std::vector<T>& Scales);
};

template <class T>
LinearSolver<T>::LinearSolver(Matrix<T>& init_A, std::vector<T> init_b)
{
    assert(init_A.numrows() == init_b.size());
    assert(init_A.numrows() == init_A.numcolumns()); // only square for now

    A = init_A;
    b = init_b;
}

template <class T>
std::vector<T> LinearSolver<T>::gaus_elim()
{
    std::vector<T> Solutions(A.numcolumns());
    std::vector<T> TempRow(A.numcolumns());

    find_scales();

    return Solutions;
}

template <class T>
std::vector<T> LinearSolver<T>::find_scales()
{
    // returns a vector containing the largest magnitude of each row
    std::vector<T> Scales(A.numrows());
    std::vector<std::thread> Threads;

    auto mod = A.numrows()%std::thread::hardware_concurrency();
    std::size_t start, end;
    for (std::size_t i = 0; i < std::thread::hardware_concurrency(); i++)
    {
        start = (A.numrows()/std::thread::hardware_concurrency())*i;
        end   = (A.numrows()/std::thread::hardware_concurrency())*(i+1);
        if(mod)
        {
            if (i < mod)
            {
                start += i;
                end   += i+1;
            } else {
                start += mod;
                end   += mod;
            }
        } else {
            start += mod*(i+1);
            end   += mod*(i+1);
        }
        if (start != end)
        {
            Threads.push_back(std::thread(
                &LinearSolver::find_scales_helper, this, start, end,
                std::ref(Scales)
            ));
        }
    }
    for (auto& t : Threads)
        t.join();

    for (auto& s : Scales)
        std::cout << s << ", ";

    return Scales;
}

template <class T>
void LinearSolver<T>::find_scales_helper(unsigned start, unsigned end,
                                         std::vector<T>& Scales)
{
    for (unsigned i = start; i < end; i++)
    {
        Scales[i] = *std::max_element(
            A.slice_begin(i,0,i,A.numcolumns()-1),
            A.slice_end(i,0,i,A.numcolumns()-1),
            [] (T a, T b) { return std::abs(a) < std::abs(b); }
        );
    }
}

} // namespace la

#endif // LA_LINEARSOLVER_H
