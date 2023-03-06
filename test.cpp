#include "map/map.hpp"
#include <iostream>
#include <map>
#include <list>

int main(void)
{
    typedef ft::map<int, int>::value_type T3;
    // std::map<int, int> mp;
    ft::map<int, int> my_mp;

    std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i + 1, (i + 1) * 3));
	ft::map<int, int> mp(lst.begin(), lst.end());

    

    std::cout << mp.max_size() << std::endl;
    std::cout << my_mp.max_size() << std::endl;

    return 0;
}