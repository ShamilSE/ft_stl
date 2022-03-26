#include "map.h"
#include "vector.h"
#include <string>
#include <vector>
#include <map>

void iterator_test_origin() {

}

int main() {
    ft::map<int, ft::vector<std::string>> m;

    // std::cout << m.size() << std::endl;

	iterator_test_origin();

	auto a = ft::make_pair("hello", 22);
	std::cout << a.first << std::endl;
	std::cout << a.second << std::endl;
}