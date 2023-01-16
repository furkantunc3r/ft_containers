#include "vector.hpp"
#include <vector>

int main(void)
{
    std::vector<int> a(5, 31, std::allocator<int>());
    ft::vector<int> ft_a;
    ft::vector<int> ft_b(std::allocator<int>);
    // ft::vector<int> ft_c(5);
    a.assign(31, 31);
    std::cout << a[31] << std::endl;
}