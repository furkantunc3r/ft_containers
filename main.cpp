#include "vector.hpp"
#include <vector>
#include <algorithm>

void pointer_func(const int *p, std::size_t size)
{
    std::cout << "data = ";
    for (std::size_t i = 0; i < size; ++i)
        std::cout << p[i] << ' ';
    std::cout << '\n';
}

void do_print(int n)
{
    std::cout << n << " ";
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
    a.reserve(1);
    ft_a.reserve(1);
    std::cout << "Def vector capacity after reserve " << a.capacity() << std::endl;
    std::cout << "Custom vector capacity after reserve " << ft_a.capacity() << std::endl;

    std::cout << "---CLEAR TEST---" << std::endl;
    std::cout << "Def vector size before clear " << a.size() << std::endl;
    std::cout << "Custom vector size before clear " << ft_a.size() << std::endl;
    a.clear();
    ft_a.clear();
    std::cout << "Def vector size after clear " << a.size() << std::endl;
    std::cout << "Custom vector size after clear " << ft_a.size() << std::endl;

    std::cout << "---ITERATOR TEST---" << std::endl;
    a.assign(5, 5);
    ft_a.assign(5, 5);
    std::cout << "Def vector for_each ";
    std::for_each(a.begin(), a.end(), do_print);
    std::cout << std::endl;
    std::cout << "Custom vector for_each ";
    std::for_each(ft_a.begin(), ft_a.end(), do_print);

    std::cout << std::endl << "---REVERSE ITERATOR TEST---" << std::endl;
    a.assign(3, 7);
    ft_a.assign(3, 7);
    std::cout << "Def vector for_each ";
    std::for_each(a.rbegin(), a.rend(), do_print);
    std::cout << std::endl;
    std::cout << "Custom vector for_each ";
    std::for_each(ft_a.rbegin(), ft_a.rend(), do_print);
    
    std::cout << std::endl << "---INSERT TEST---" << std::endl;
    a.insert(a.end(), 0);
    a.insert(a.begin(), 31);
    std::cout << "Def vector insert ";
    std::for_each(a.begin(), a.end(), do_print);
    ft_a.insert(ft_a.end(), 0);
    ft_a.insert(ft_a.begin(), 31);
    std::cout << std::endl;
    std::cout << "Custom vector insert ";
    std::for_each(ft_a.begin(), ft_a.end(), do_print);
    std::cout << std::endl;
    
    a.insert(a.begin(), 3, 31);
    std::cout << "Def vector insert ";
    std::for_each(a.begin(), a.end(), do_print);
    std::cout << std::endl;
    ft_a.insert(ft_a.begin(), 3, 31);
    std::cout << "Custom vector insert ";
    std::for_each(ft_a.begin(), ft_a.end(), do_print);
    std::cout << std::endl;
}