#include "vector.hpp"
#include <vector>

void pointer_func(const int* p, std::size_t size)
{
    std::cout << "data = ";
    for (std::size_t i = 0; i < size; ++i)
        std::cout << p[i] << ' ';
    std::cout << '\n';
}

int main(void)
{
    std::cout << std::endl;
    std::vector<int> a;
    ft::vector<int> ft_a;

    std::cout << "Initially, numbers.empty(): " << a.empty() << '\n';
    std::cout << "Initially, numbers.empty(): " << ft_a.empty() << '\n';
    
    a.assign(5, 5);
    std::cout << "After adding elements, numbers.empty(): " << a.empty() << '\n';
    ft_a.assign(5, 5);
    std::cout << "After adding elements, numbers.empty(): " << ft_a.empty() << '\n';
    
    std::cout << a.at(2) << std::endl;
    std::cout << a[3] << std::endl;
    std::cout << a.front() << std::endl;
    std::cout << a.back() << std::endl;
    pointer_func(a.data(), a.size());
    std::cout << a.max_size() << std::endl;

    std::cout << std::endl << std::endl;

    std::cout << ft_a.at(2) << std::endl;
    std::cout << ft_a[3] << std::endl;
    std::cout << ft_a.front() << std::endl;
    std::cout << ft_a.back() << std::endl;
    pointer_func(ft_a.data(), ft_a.size());
    std::cout << ft_a.max_size() << std::endl;
}