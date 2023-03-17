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
            { // when not at the end
                // stride by one row
                m_ptr = m_ptr + M.rows;
                counter = counter + 1;
                return *this;
            }
            if (counter == M.rows*M.columns)
            { // if we've visited all the addresses
                // stride by one address
                m_ptr = m_ptr + 1;
                return *this;
            }
            // when at the end of a column
            // stride to the next column
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
    class Slice
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = value_type*;
        using reference         = value_type&;
    public:
        Slice(pointer ptr, Matrix &Owner,
              std::size_t start_row, std::size_t start_col,
              std::size_t end_row, std::size_t end_col) :
              m_ptr(ptr), M(Owner),
              sr(start_row), sc(start_col),
              er(end_row), ec(end_col) {}
        reference operator*() const {return *m_ptr;}
        pointer operator->() {return m_ptr;}
        Slice& operator++()
        {
            if (counter%((ec-sc)+1) == 0)
            { // when we're not the end of the slice's row
                std::cout <<"end of row, " << counter << std::endl;
                // get to the next row of the slice
                m_ptr += M.columns-(ec-sc);
                counter += 1;
                return *this;
            }
            // default behavior is to advance by one
            std::cout << "default" << ", " << counter << std::endl;
            m_ptr += 1;
            counter += 1;
            return *this;
        }
        Slice operator++(int)
            {Slice tmp = *this; ++(*this); return tmp;}
        friend bool operator== (const Slice& a,const Slice& b)
            {return a.m_ptr == b.m_ptr;}
        friend bool operator!= (const Slice& a,const Slice& b)
            {return a.m_ptr != b.m_ptr;}
    private:
        pointer m_ptr;
        Matrix<T> M;
        size_t sr, sc, er, ec;
        unsigned counter = 1;
    };
    auto slice_begin(std::size_t start_row, std::size_t start_col,
                     std::size_t end_row,   std::size_t end_col)
    {
        return Slice(&data[start_row*rows+start_col], *this,
                     start_row, start_col, end_row, end_col);
    }
    auto slice_end(std::size_t start_row, std::size_t start_col,
                   std::size_t end_row,   std::size_t end_col)
    {
        return Slice(
            &data[(end_row+1)*rows+(end_col-(end_col-start_col))], *this,
            start_row, start_col, end_row, end_col);
    }

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
    Matrix<T> strassen_mult(Matrix<T> M2);

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
    // this could also be threaded, but it's not taking much time as is and
    // getting a generator for each thread that has good seeds is non-trivial.
    // Maybe I'll improve it later
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

    auto newMatrix = Matrix<T>(rows, M2.columns, 0.0);
    /*
     * Huang, Jianyu; Smith, Tyler M.; Henry, Greg M.; van de Geijn, Robert A.
     * (13 Nov 2016) found that Strassan's algorithm becomes useful at about
     * 512x512.
     */

    if (columns < 512)
    {
        newMatrix = naive_mult(M2);
    } else {
       //Matrix<T> tempMatrix[4];
    }
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
            std::thread(&Matrix<T>::mult_helper, this,
                        std::ref(M2), std::ref(newMatrix), i)
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
    auto remainder = rows%std::thread::hardware_concurrency();

    std::size_t start = (rows/std::thread::hardware_concurrency())*thread_idx;
    std::size_t end = (rows/std::thread::hardware_concurrency())*(thread_idx+1);
    if(remainder)
    {
        // when the number of rows is not divisible by the number of threads...
        if (thread_idx < remainder)
        {
            // and the thread needs to do an extra loop...
            // add the index to the start, because this is equal to the number
            // of threads before it that had to do an extra loop,
            start += thread_idx;
            // and increase the end by one plus the index to give it more work.
            end += thread_idx+1;
        } else {
            // and the thread does not need to do an extra loop...
            // add the index to the start, because this is equal to the number
            // of threads before it that had to do an extra loop,
            start += thread_idx;
            // and add the index to the end, becuase this thread doesn't need to
            // do extra work.
            end += thread_idx;
        }
    } else {
        // when the number of rows is divisible by the number of threads, divide
        // the work trivially
        start += remainder*(thread_idx+1);
        end += remainder*(thread_idx+1);
    }


    for (std::size_t i = start; i < end; i++)
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

template <class T>
Matrix<T> Matrix<T>::strassen_mult(Matrix<T> M2)
{
    /*
     * An obvious way to thread Strassen's method is to create a thread for each
     * of the 7 child multiplications. On my system, this is unideal becuase I
     * only have two physical cores and four logcal threads. The result of this
     * would be multiple naive multiplications running in parallel, but this is
     * no more efficient than performing each multiplication with a threaded
     * implimentation serially. So, I only have to impliment Strassen in a
     * serial way and any desireable parallelization is handled by my already
     * written naive algorithm.
     */
    assert(rows == columns && rows%2 == 0); // will impliment padding later
    auto newMatrix = Matrix<T>(rows, M2.columns);

    std::size_t size = rows/2;
    std::vector<Matrix<T>> Intermediates(8, Matrix(size, size));

    for (size_t i = 0; i < size; i++)
    {
        for (unsigned j = 0; j < size; j++)
        {
            Intermediates[0].set(i,j, (i,j));
            Intermediates[1].set(i,j, (i,size+j));
            Intermediates[2].set(i,j, (size+i,j));
            Intermediates[3].set(i,j, (size+i,size+j));

        }
    }
}

} // namespace la

#endif // LA_MATRIX
