//
// Created by Mussels Ismene on 5/14/22.
//

#include "map.h"

int main()
{
    ft::map<int,int> a;

    a.insert(ft::make_pair(1, 5));
    a.insert(ft::make_pair(5, 4));
    a.insert(ft::make_pair(3, 9));
    a.insert(ft::make_pair(4, 16));

    std::cout << "map_main" << std::endl;
}