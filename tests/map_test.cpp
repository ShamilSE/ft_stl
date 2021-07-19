#include "../map.hpp"
#include "../vector.hpp"
#include <string>
#include <vector>
#include <map>

void iterator_test_origin() {

}

void map_test() {
    ft::map<int, ft::vector<std::string>> m;

    // std::cout << m.size() << std::endl;

	iterator_test_origin();

	auto a = ft::make_pair("hello", 22);
	std::cout << a.first << std::endl;
	std::cout << a.second << std::endl;
}