#pragma once

namespace ft {

template<class Category, class T>
struct    iterator_traits
{
    typedef T                value_type;
    typedef value_type*        pointer;
    typedef value_type&        reference;
    typedef ptrdiff_t        difference_type;
    typedef Category        iterator_category;
};

typedef size_t size_type;

bool is_integral();

template<typename T, typename Allocator = std::allocator<T> >
class vector;

//enable_if
template<bool B, class T = void>
struct    enable_if {};

template<class T>
struct    enable_if<true, T> { typedef T type; };

}