#pragma once

#include <memory>
#include <iostream>

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

//enable_if
template<bool B, class T = void>
struct    enable_if {};

template<class T>
struct    enable_if<true, T> { typedef T type; };

//pair
template<typename T1, typename T2>
struct pair
{
    T1& first;
    T2& second;

    pair(T1& f, T2& s): first(f), second(s) {}
};

template<typename T1, typename T2, typename Allocator = std::allocator<ft::pair<T1, T2>>>
pair<T1, T2>& make_pair(T1 first, T2 second)
{
    Allocator allocator;
    ft::pair<T1, T2>* new_pair = allocator.allocate(1);
    new(new_pair) pair<T1, T2>(first, second);
    return *new_pair;
}

//container headers
    template<typename T, typename Allocator = std::allocator<T> >
    class vector;

    template<typename Key, typename Tp, typename Compare = std::less<Key>,
            typename Allocator = std::allocator<ft::pair<Key, Tp> > >
    class map;

}
