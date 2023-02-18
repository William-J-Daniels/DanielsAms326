#ifndef LA_MATRIX
#define LA_MATRIX

#include <vector>
#include <cassert>
#include <iterator>
#include <cstddef>

namespace la {

template <class T>
class Matrix
{
public:
    // constructors
    Matrix() = default;
    Matrix(std::size_t init_rows, std::size_t init_columns);
    Matrix(std::size_t init_rows, std::size_t init_columns, T init_val);

    // accessors and mutators
    std::size_t numrows() { return rows; }
    std::size_t numcolumns() { return columns; }
    T operator() (std::size_t row, std::size_t column);
    void set(std::size_t row, std::size_t column, T val)
        { data[row*column + column] = val; } // replace later, running out of time now

    // iterators -- impliment others as need arises, hw due soon
    // class Column_Iterator
    // {
    //     using iterator_category = std::forward_iterator_tag;
    //     using difference_type   = std::ptrdiff_t;
    //     using value_type        = double;//std::vector<T>;
    //     using pointer           = double*;//std::vector<T>*;
    //     using reference         = double&;//std::vector<T>&;
    // public:
    //     Column_Iterator(pointer ptr, Matrix Parent)
    //         { m_ptr = ptr; this->m_outer = Parent; }
    //     reference operator*() const { return *m_ptr; }
    //     pointer operator->() { return m_ptr; }
    //     Column_Iterator& operator++()
    //         { m_ptr = m_ptr + m_outer.columns; return *this; }
    //     Column_Iterator operator++(int)
    //         { Column_Iterator tmp = *this; *this = *this + m_outer.columns;
    //             return tmp; }
    //     friend bool operator== (const Column_Iterator &a,
    //                             const Column_Iterator &b)
    //         { return a.m_ptr == b.m_ptr; }
    //     friend bool operator!= (const Column_Iterator &a,
    //                             const Column_Iterator &b)
    //         { return a.m_ptr != b.m_ptr; }
    // private:
    //     pointer m_ptr;
    //     Matrix  m_outer;
    // };
    // Column_Iterator begin() { return Column_Iterator(&data[0]); }
    // Column_Iterator end()   { return Column_Iterator(&data[rows*columns]); }

private:
    std::size_t rows, columns;
    std::vector<T> data;
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
T Matrix<T>::operator() (std::size_t row, std::size_t column)
{
    assert(row >= 0 && row < rows);
    assert(column >= 0 && column < columns);

    return data[row*columns + column];
}

} // namespace la

#endif // LA_MATRIX
