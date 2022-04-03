#include "map.h"
#include "vector.h"

int main() {
    ft::map<int, int> a;
    a.insert(ft::make_pair(1, 5));
    a.insert(ft::make_pair(5, 4));
    a.insert(ft::make_pair(3, 9));
    //a.insert(ft::make_pair(4, 16));

    ft::map<int, int>::iterator it = a.begin();
    it++;
    it++;
    it++;
    return 0;
}