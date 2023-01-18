#include "vector.hpp"
#include <vector>

void pointer_func(const int *p, std::size_t size)
{
    std::cout << "data = ";
    for (std::size_t i = 0; i < size; ++i)
        std::cout << p[i] << ' ';
    std::cout << '\n';
}

int main(void)
{
    std::vector<int> a;
    ft::vector<int> ft_a;

    std::cout << "---EMPTY AND ASSING TEST---" << std::endl;
    std::cout << "Initially, def vector.empty(): " << a.empty() << '\n';
    std::cout << "Initially, custom vector.empty(): " << ft_a.empty() << '\n';
    a.assign(5, 5);
    ft_a.assign(5, 5);
    std::cout << "After adding elements, def vector.empty(): " << a.empty() << '\n';
    std::cout << "After adding elements, custom vector.empty(): " << ft_a.empty() << '\n';

    std::cout << "--ELEMENT ACCESS TEST---" << std::endl;
    std::cout << "Default vector" << std::endl;
    std::cout << a.at(2) << std::endl;
    std::cout << a[3] << std::endl;
    std::cout << a.front() << std::endl;
    std::cout << a.back() << std::endl;
    std::cout << a.max_size() << std::endl;
    pointer_func(a.data(), a.size());
    std::cout << "My vector" << std::endl;
    std::cout << ft_a.at(2) << std::endl;
    std::cout << ft_a[3] << std::endl;
    std::cout << ft_a.front() << std::endl;
    std::cout << ft_a.back() << std::endl;
    pointer_func(ft_a.data(), ft_a.size());
    std::cout << ft_a.max_size() << std::endl;
    
    std::cout << "---RESERVE TEST---" << std::endl;
    std::cout << "Def vector capacity before reserve " << a.capacity() << std::endl;
    std::cout << "Custom vector capacity before reserve " << ft_a.capacity() << std::endl;
    a.reserve(10);
    ft_a.reserve(10);
    std::cout << "Def vector capacity after reserve " << a.capacity() << std::endl;
    std::cout << "Custom vector capacity after reserve " << ft_a.capacity() << std::endl;

    
    std::cout << "---CLEAR TEST---" << std::endl;
    std::cout << "Def vector size before clear " << a.size() << std::endl;
    std::cout << "Custom vector size before clear " << ft_a.size() << std::endl;
    a.clear();
    ft_a.clear();
    std::cout << "Def vector size after clear " << a.size() << std::endl;
    std::cout << "Custom vector size after clear " << ft_a.size() << std::endl;

    // Iterator test
    ft::vector<int>::iterator it;
    it = ft_a.begin();
    std::cout << *it << std::endl;
    std::cout << *(it++) << std::endl;
}