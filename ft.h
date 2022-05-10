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

template<bool B, class T = void>
struct    enable_if {};

template<class T>
struct    enable_if<true, T> { typedef T type; };

template<typename T1, typename T2>
struct pair
{
    T1 first;
    T2 second;

    /*    default constructor    */
    pair() : first(T1()), second(T2()) {}

    /*    filling    constructor    */
    pair(T1& f, T2& s): first(f), second(s) {}

    /*    converting constructor    */
    template<class _U1, class _U2>
    pair(const pair<_U1, _U2> &p) : first(p.first), second(p.second) {}

    /*    copy constructor    */
    //pair(const pair &other) { *this = other; }
};

template<typename T1, typename T2>
pair<T1, T2> make_pair(T1 first, T2 second) { return pair<T1,T2>(first, second); }

template<typename T, typename Allocator = std::allocator<T> >
class vector;

template<typename Key, typename Tp, typename Compare = std::less<Key>,
        typename Allocator = std::allocator<ft::pair<Key, Tp> > >
class map;

}
