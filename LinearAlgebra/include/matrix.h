#ifndef LA_MATRIX
#define LA_MATRIX

#include <uniformgenerator.h>
#include <vector>
#include <cassert>
#include <iterator>
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <thread>
#include <cstdlib>

namespace la {

    // BIG todo: make thing pass by reference

template <class T>
class Matrix
{
public:
    // constructors
    Matrix() = default;
    Matrix(std::size_t init_rows, std::size_t init_columns);
    Matrix(std::size_t init_rows, std::size_t init_columns, T init_val);
    // creation routines
    void rand(T current_seed, T previous_seed);

    // accessors and mutators
    std::size_t numrows() { return rows; }
    std::size_t numcolumns() { return columns; }
    T operator() (std::size_t row, std::size_t column);
    friend std::ostream& operator<< (std::ostream& out, const Matrix<T>& M)
    {
        for (int row = 0; row < M.rows; row++)
        {
            for (int column = 0; column < M.columns; column++)
            {
                out << M.data[row*M.columns + column] << " ";
            }
            out << std::endl;
        }
        return out;
    }

    void set(std::size_t row, std::size_t column, T val);

    // iterators
    // row iterator is just the iterator of the internal vector
    auto row_begin() {return data.begin();}
    auto row_end()   {return data.end();}
    class columnIterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = value_type*;
        using reference         = value_type&;
    public:
        columnIterator(pointer ptr, Matrix &Owner) : m_ptr(ptr), M(Owner) {}
        reference operator*() const {return *m_ptr;}
        pointer operator->() {return m_ptr;}
        columnIterator& operator++()
        {
            if (counter%M.columns != 0)
            {
                m_ptr = m_ptr + M.rows;
                counter = counter + 1;
                return *this;
            }
            if (counter == M.rows*M.columns)
            {
                m_ptr = m_ptr + 1;
                return *this;
            }
            m_ptr = m_ptr - M.rows * (M.columns - 1) + 1;
            counter = counter + 1;
            return *this;
        }
        columnIterator operator++(int)
            {columnIterator tmp = *this; ++(*this); return tmp;}
        friend bool operator== (const columnIterator& a,const columnIterator& b)
            {return a.m_ptr == b.m_ptr;}
        friend bool operator!= (const columnIterator& a,const columnIterator& b)
            {return a.m_ptr != b.m_ptr;}
    private:
        pointer m_ptr;
        Matrix<T> M;
        unsigned counter = 1;
    };
    auto column_begin() {return columnIterator(&data[0],            *this);}
    auto column_end()   {return columnIterator(&data[rows*columns], *this);}

    // matrix operations (will grow over time)
    Matrix<T> operator- ();
    Matrix<T> operator+ (Matrix<T> M2);
    Matrix<T> operator- (Matrix<T> M2);

    friend Matrix<T> operator* (T scalar, Matrix<T> M)
    {
        auto newMatrix = Matrix(M.rows, M.columns);

        for (std::size_t i = 0; i < M.data.size(); i++)
            newMatrix.data[i] = scalar * M.data[i];

        return newMatrix;
    }
    friend Matrix<T> operator* (Matrix<T> M, T scalar)
    {
        auto newMatrix = Matrix(M.rows, M.columns);

        for (std::size_t i = 0; i < M.data.size(); i++)
            newMatrix.data[i] = scalar * M.data[i];

        return newMatrix;
    }
    Matrix<T> operator* (Matrix<T> M2);
    Matrix<T> naive_mult(Matrix<T> M2);

private:
    std::size_t rows, columns;
    std::vector<T> data;

    void mult_helper(Matrix<T>& M2, Matrix<T>& Mout, size_t thread_idx);
};

template<class T>
Matrix<T>::Matrix(std::size_t init_rows, std::size_t init_columns)
{
    assert(init_rows > 0 && init_columns > 0);

    rows = init_rows;
    columns = init_columns;

    data = std::vector<T>(rows*columns);
}

template <class T>
Matrix<T>::Matrix(std::size_t init_rows, std::size_t init_columns, T init_val)
{
    assert(init_rows > 0 && init_columns > 0);

    rows = init_rows;
    columns = init_columns;

    data = std::vector<T>(rows*columns, init_val);
}

template <class T>
void Matrix<T>::rand(T current_seed, T previous_seed)
{
    auto Rng = rng::UniformGenerator(current_seed, previous_seed);

    for (auto& d : data)
        d = Rng();
}

template <class T>
T Matrix<T>::operator() (std::size_t row, std::size_t column)
{
    assert(row >= 0 && row < rows);
    assert(column >= 0 && column < columns);

    return data[row*columns + column];
}

template <class T>
void Matrix<T>::set(std::size_t row, std::size_t column, T val)
{
    data[row*columns + column] = val;
}

// matrix operations

template <class T>
Matrix<T> Matrix<T>::operator-()
{
    auto newMatrix = Matrix<T>(rows, columns);
    std::transform(row_begin(), row_end(),
                   newMatrix.row_begin(),
                   [](T i){return -i;});

    return newMatrix;
}

template <class T>
Matrix<T> Matrix<T>::operator+ (Matrix<T> M2)
{
    // only defined for matrices of the same datatype
    assert(rows == M2.rows && columns == M2.columns);

    auto newMatrix = Matrix<T>(rows, columns);
    std::transform(row_begin(), row_end(),
                   M2.row_begin(),
                   newMatrix.row_begin(),
                   [](T i, T j){return i+j;});

    return newMatrix;
}

template <class T>
Matrix<T> Matrix<T>::operator- (Matrix<T> M2)
{
    assert(rows == M2.rows && columns == M2.columns);

    auto newMatrix = Matrix<T>(rows, columns);
    std::transform(row_begin(), row_end(),
                   M2.row_begin(),
                   newMatrix.row_begin(),
                   [](T i, T j){return i-j;});

    return newMatrix;
}

template <class T>
Matrix<T> Matrix<T>::operator*(Matrix<T> M2)
{
    assert(columns = M2.rows);
    double sum;

    auto newMatrix = Matrix<T>(rows, M2.columns, 0.0);
    /*
     * Huang, Jianyu; Smith, Tyler M.; Henry, Greg M.; van de Geijn, Robert A.
     * (13 Nov 2016) found that Strassan's algorithm becomes useful at about
     * 512x512.
     */

    //if (columns < 512)
    //{
        for (std::size_t i = 0; i < rows; i ++)
        {
            for (std::size_t j = 0; j < M2.columns; j++)
            {
                sum = 0.0;
                for (std::size_t k = 0; k < columns; k++)
                {
                    sum += data[i*columns + k] * M2(k, j);
                    //std::cout << sum << ", ";
                }
                //std::cout << i << ", " << j << std::endl;
                newMatrix.set(i, j, sum);
                //std::cout << std::endl;
            }
            //std::cout << std::endl;
        }
        //return newMatrix;
    //} else {
    //    Matrix<T> tempMatrix[4];
    //}
return newMatrix;
}

template <class T>
Matrix<T> Matrix<T>::naive_mult(Matrix<T> M2)
{
    std::vector<std::thread> Threads;
    auto newMatrix = Matrix<T>(rows, M2.columns);

    for (unsigned i = 0; i < std::thread::hardware_concurrency(); i++)
    {
        Threads.push_back(
            std::thread(&Matrix<T>::mult_helper, this, std::ref(M2), std::ref(newMatrix), i)
        );
    }

    for (auto& t : Threads)
        t.join();

    return newMatrix;
}

template <class T>
void Matrix<T>::mult_helper(Matrix<T>& M2, Matrix<T>& Mout, size_t thread_idx)
{
    double sum;

    for (std::size_t i = (rows/std::thread::hardware_concurrency())*thread_idx;
         i < (rows/std::thread::hardware_concurrency())*(thread_idx+1);
         i++)
    {
        for (std::size_t j = 0; j < M2.columns; j++)
        {
            sum = 0.0;
            for (std::size_t k = 0; k < columns; k++)
            {
                sum += data[i*columns+k] * M2(k,j);
            }
            Mout.set(i,j, sum);
        }
    }
}

} // namespace la

#endif // LA_MATRIX
