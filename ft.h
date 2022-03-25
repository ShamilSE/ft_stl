#pragma once

namespace ft {

template<class _Category, class _T>
struct    iterator_traits
{
    typedef _T                value_type;
    typedef value_type*        pointer;
    typedef value_type&        reference;
    typedef ptrdiff_t        difference_type;
    typedef _Category        iterator_category;
};

typedef size_t size_type;

bool is_integral();

template<typename T, typename Allocator = std::allocator<T> >
class vector;

}