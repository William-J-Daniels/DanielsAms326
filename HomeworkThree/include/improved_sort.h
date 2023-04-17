#ifndef IM_SORT
#define IM_SORT

// https://artificial-mind.net/blog/2020/11/28/std-sort-multiple-ranges

#include <vector>
#include <algorithm>
#include <iostream>

struct val
{
    double key;
    double value;
};

struct ref
{
    double* key;
    double* value;

    ref& operator=(ref&& r)
    {
        *key = std::move(*r.key);
        *value = std::move(*r.value);
        return *this;
    }

    ref& operator=(val&& r)
    {
        *key = std::move(r.key);
        *value = std::move(r.value);
        return *this;
    }

    friend void swap(ref a, ref b)
    {
        std::swap(*a.key, *b.key);
        std::swap(*a.value, *b.value);
    }

    operator val() && { return {std::move(*key), std::move(*value)}; }
};

bool operator<(ref const& a, val const& b)
{
    return *a.key < b.key;
}

bool operator<(val const& a, ref const& b)
{
    return a.key < *b.key;
}

bool operator<(ref const& a, ref const& b)
{
    return *a.key < *b.key;
}

struct sort_it
{
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = int64_t;
    using value_type = val;
    using pointer = value_type*;
    using reference = ref;

    size_t index;
    double* keys;
    double* values;

    bool operator==(sort_it const& r) const { return index == r.index; }
    bool operator!=(sort_it const& r) const { return index != r.index; }

    sort_it operator+(difference_type i) const { return {index + i, keys, values}; }
    sort_it operator-(difference_type i) const { return {index - i, keys, values}; }

    difference_type operator-(sort_it const& r) const
    {
        return difference_type(index) - difference_type(r.index);
    }

    sort_it& operator++()
    {
        ++index;
        return *this;
    }
    sort_it& operator--()
    {
        --index;
        return *this;
    }

    bool operator<(sort_it const& r) const { return index < r.index; }

    ref operator*() { return {keys + index, values + index}; }
};

#endif // IM_SORT
