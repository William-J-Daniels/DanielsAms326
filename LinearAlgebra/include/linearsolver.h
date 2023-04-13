#ifndef LA_LINEARSOLVER_H
#define LA_LINEARSOLVER_H

#include <matrix.h>
#include <vector>
#include <cassert>
#include <thread>
#include <algorithm>
#include <cmath>
#include <limits>

#include <iostream>

namespace la {

template <class T>
class LinearSolver
{
    // solves linear systems of the form  Ax=b for x
    // takes a reference to the data, if you need the original make a copy
public:
    LinearSolver() = default;
    LinearSolver<T>(Matrix<T> init_A, std::vector<T> init_b);

    void set_max_iter(unsigned new_max_iter) { max_iter = new_max_iter; }
    void set_precision(double new_precision) { precision = new_precision; }

    std::vector<T> gaus_elim();
    std::vector<T> jacobi_iter(std::vector<T> InitGuess);
    std::vector<T> gauss_seidel(std::vector<T> InitGuess);
    std::vector<T> SOR(std::vector<T> InitGuess, T relaxation);

private:
    Matrix<T> A;
    std::vector<T> b;
    std::vector<T> Solutions;

    double precision = 1.0e-8;
    unsigned num_iter = 0;
    unsigned max_iter = std::numeric_limits<unsigned>::infinity();

    unsigned num_pivots = 0;

    std::vector<T> find_scales();
    void find_scales_helper(unsigned start, unsigned end,
                            std::vector<T>& Scales);
    void swap_rows(std::size_t north, std::size_t south);
    void swap_rows(std::size_t north, std::size_t south,
                   std::vector<T> extra_vec);
    void forward_eliminate(std::size_t startr, std::size_t endr,
                           std::size_t current_row);
    void back_substitution();
};

template <class T>
LinearSolver<T>::LinearSolver(Matrix<T> init_A, std::vector<T> init_b)
{
    assert(init_A.numrows() == init_b.size());
    assert(init_A.numrows() == init_A.numcolumns()); // only square for now

    A = init_A;
    b = init_b;
}

template <class T>
std::vector<T> LinearSolver<T>::gaus_elim()
{
    Solutions = std::vector<T>(A.numcolumns());
    auto Scales = find_scales();
    double scaled_col, col_max, row_max_idx;
    std::size_t mod, start, end; // for distributing work to threads

    for (std::size_t current_row = 0; current_row < A.numrows(); current_row++)
    { // loop over all rows
        std::vector<std::thread> Threads;
        // first we loop for pivoting opperturnities
        col_max = std::numeric_limits<T>::lowest();
        row_max_idx = current_row;
        for (std::size_t prow = current_row; prow < A.numrows(); prow++)
        {
            scaled_col = std::abs(A(prow, current_row)) / Scales[prow];
            if (scaled_col > col_max)
            {
                col_max = scaled_col;
                row_max_idx = prow;
            }
        }
        if (row_max_idx-current_row)
            swap_rows(row_max_idx, current_row, Scales);

        // forward eliminate
        #pragma omp parallel for
        for (std::size_t erow = current_row + 1; erow < A.numrows(); ++erow)
        {
            auto factor = A(erow, current_row) / A(current_row, current_row);
            for (std::size_t ecol = current_row + 1; ecol < A.numcolumns(); ++ecol)
            {
                A.set(erow, ecol, A(erow,ecol) - A(current_row, ecol) * factor);
            }
            A.set(erow, current_row, 0.0);
            b[erow] = b[erow] - b[current_row]*factor;
        }

    }
    back_substitution();

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

template <class T>
void LinearSolver<T>::swap_rows(std::size_t north, std::size_t south)
{
    // can be parallelized later
    std::vector<T> RowTemp(A.numcolumns());
    T VecTemp;

    std::copy(
        A.slice_begin(north,0,north,A.numcolumns()),
        A.slice_end(north,0,north,A.numcolumns()),
        RowTemp.begin()
    );

    std::copy(
        A.slice_begin(south,0,south,A.numcolumns()),
        A.slice_end(south,0,south,A.numcolumns()),
        A.slice_begin(north,0,north,A.numcolumns())
    );

    std::copy(
        RowTemp.begin(),
        RowTemp.end(),
        A.slice_begin(south,0,south,A.numcolumns())
    );

    VecTemp = b[north];
    b[north] = b[south];
    b[south] = VecTemp;

    num_pivots++;
}

template <class T>
void LinearSolver<T>::swap_rows(std::size_t north, std::size_t south,
                   std::vector<T> extra_vec)
{
    T VecTemp;

    swap_rows(north, south);

    VecTemp = extra_vec[north];
    extra_vec[north] = extra_vec[south];
    extra_vec[south] = VecTemp;
}

template <class T>
void LinearSolver<T>::back_substitution()
{
    Solutions[A.numcolumns()-1] = b[A.numcolumns()-1]/A(A.numcolumns()-1, A.numcolumns()-1);

    for (int brow = (A.numcolumns()-2); brow >= 0; --brow)
    {
        double sum = b[brow];
        for (std::size_t bcol = brow+1; bcol < A.numcolumns(); ++bcol)
        {
            sum = sum - A(brow, bcol) * Solutions[bcol];
        }
        Solutions[brow] = sum / A(brow, brow);
    }
}

template <class T>
std::vector<T> LinearSolver<T>::jacobi_iter(std::vector<T> InitGuess)
{
    assert(A.numrows() == A.numcolumns());
    assert(InitGuess.size() == A.numrows());

    Solutions = InitGuess;
    auto D = DiagonalMatrix<T> {A.diag()};
    auto R = A - D;
    D.invert();

    // last_slns, temp, diffs;
    std::vector<T> last_slns, temp, diffs (Solutions.size());
    do
    {
        temp = b - (R*Solutions);
        Solutions = D * temp;
        num_iter++;
    } while (num_iter < max_iter); // add convergence later

    return Solutions;
}

template <class T>
std::vector<T> LinearSolver<T>::gauss_seidel(std::vector<T> InitGuess)
{
    // use element- based formula from
    // https://en.wikipedia.org/wiki/Gauss%E2%80%93Seidel_method
    assert(A.numrows() == A.numcolumns());
    assert(InitGuess.size() == A.numrows());

    Solutions = InitGuess;

    do{
        for (std::size_t i = 0; i < Solutions.size(); i++)
        {
            double sum = 0.0;
            for (std::size_t j = 0; j < i; j++)
                sum += A(i,j) * Solutions[j];
            for (std::size_t j = i+1; j < Solutions.size(); j++)
                sum += A(i,j) * Solutions[j];

            Solutions[i] = 1.0 / A(i, i) * (b[i] - sum);
        }
        num_iter++;
    } while (num_iter < max_iter);

    return Solutions;
}

template <class T>
std::vector<T> LinearSolver<T>::SOR(std::vector<T> InitGuess, T relaxation)
{
    assert(A.numrows() == A.numcolumns());
    assert(InitGuess.size() == A.numrows());

    Solutions = InitGuess;

    do{
        for (std::size_t i = 0; i < Solutions.size(); i++)
        {
            double sum = 0.0;
            for (std::size_t j = 0; j < i; j++)
                sum += A(i,j) * Solutions[j];
            for (std::size_t j = i+1; j < Solutions.size(); j++)
                sum += A(i,j) * Solutions[j];

            Solutions[i] = (1.0 - relaxation) * Solutions[i] +
            (relaxation / A(i, i) * (b[i] - sum));
        }
        num_iter++;
    } while (num_iter < max_iter);

    return Solutions;
}

} // namespace la

#endif // LA_LINEARSOLVER_H
