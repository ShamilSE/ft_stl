#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>

namespace ft {

    template<typename T, typename Allocator = std::allocator<T> >
    class vector {
    private:
        T *_content;

    public:
        vector() {
            std::cout << "vector constructed" << std::endl;
        }

        vector(const vector<T> &);

        vector &operator=(const vector<T> &);

        ~vector() {
            std::cout << "vector destructed" << std::endl;
        }

        class vectorIterator {
        public:
            T &item;
        };
    };

}

#endif