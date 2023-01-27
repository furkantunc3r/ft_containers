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
    ft::vector<int> ft_a;
    ft::vector<int> ft_c;

    std::cout << "---EMPTY AND ASSING TEST---" << std::endl;
    std::cout << "Initially, vector.empty(): " << ft_a.empty() << '\n';
    ft_a.assign(5, 5);
    ft_c.assign(ft_a.begin(), ft_a.end());
    std::cout << "Vector c ";
    pointer_func(ft_c.data(), ft_c.size());
    
    std::cout << "After adding elements, vector.empty(): " << ft_a.empty() << '\n';

    std::cout << "--ELEMENT ACCESS TEST---" << std::endl;
    std::cout << ft_a.at(2) << std::endl;
    std::cout << ft_a[3] << std::endl;
    std::cout << ft_a.front() << std::endl;
    std::cout << ft_a.back() << std::endl;
    pointer_func(ft_a.data(), ft_a.size());
    std::cout << ft_a.max_size() << std::endl;
    
    std::cout << "---RESERVE TEST---" << std::endl;
    std::cout << "Vector capacity before reserve " << ft_a.capacity() << std::endl;
    ft_a.reserve(1);
    std::cout << "Vector capacity after reserve " << ft_a.capacity() << std::endl;

    std::cout << "---CLEAR TEST---" << std::endl;
    std::cout << "Vector size before clear " << ft_a.size() << std::endl;
    ft_a.clear();
    std::cout << "Vector size after clear " << ft_a.size() << std::endl;

    std::cout << "---ITERATOR TEST---" << std::endl;
    ft_a.assign(5, 5);
    std::cout << "Vector for_each ";
    std::for_each(ft_a.begin(), ft_a.end(), do_print);

    std::cout << std::endl << "---REVERSE ITERATOR TEST---" << std::endl;
    ft_a.assign(3, 7);
    std::cout << "Vector for_each ";
    std::for_each(ft_a.rbegin(), ft_a.rend(), do_print);
    
    std::cout << std::endl << "---INSERT TEST---" << std::endl;
    ft_a.insert(ft_a.end(), 0);
    ft_a.insert(ft_a.begin(), 31);
    std::cout << "Vector insert ";
    std::for_each(ft_a.begin(), ft_a.end(), do_print);
    std::cout << std::endl;
    
    ft_a.insert(ft_a.begin(), 3, 31);
    std::cout << "Vector insert ";
    std::for_each(ft_a.begin(), ft_a.end(), do_print);
    std::cout << std::endl;

    std::cout << "---ERASE TEST---" << std::endl;
    ft_a.erase(ft_a.end() - 1);
    std::cout << "Vector after erase ";
    std::for_each(ft_a.begin(), ft_a.end(), do_print);
    std::cout << std::endl;

    std::cout << "---PUSH-POP BACK TEST---" << std::endl;
    ft_a.push_back(21);
    std::cout << "Vector after erase ";
    std::for_each(ft_a.begin(), ft_a.end(), do_print);
    std::cout << std::endl;
    ft_a.pop_back();
    std::cout << "Vector after pop ";
    std::for_each(ft_a.begin(), ft_a.end(), do_print);
    
    std::cout << std::endl << "---RESIZE TEST---" << std::endl;
    ft_a.resize(5, 0);
    std::cout << "Vector after resize ";
    std::for_each(ft_a.begin(), ft_a.end(), do_print);
    std::cout << std::endl;
    ft_a.resize(10, 69);
    std::cout << "Vector after resize ";
    std::for_each(ft_a.begin(), ft_a.end(), do_print);
    std::cout << std::endl;

    std::cout << "---SWAP TEST---" << std::endl;
    ft::vector<int> ft_b;
    ft_b.assign(10, 1);
    ft_b.swap(ft_a);
    std::cout << "Vector after swap ";
    std::for_each(ft_a.begin(), ft_a.end(), do_print);
    std::cout << std::endl;

    std::cout << "---OPERATOR TEST---" << std::endl;
    ft_c.assign(10, 1);
    std::cout << "A :";
    std::for_each(ft_a.begin(), ft_a.end(), do_print);
    std::cout << std::endl;
    std::cout << "B :";
    std::for_each(ft_b.begin(), ft_b.end(), do_print);
    std::cout << std::endl;
    std::cout << "C :";
    std::for_each(ft_c.begin(), ft_c.end(), do_print);
    std::cout << std::endl;
    std::cout << "A == B : " << (ft_a == ft_b) << std::endl;
    std::cout << "A == C : " << (ft_a == ft_c) << std::endl;
    std::cout << "A != B : " << (ft_a != ft_b) << std::endl;
    std::cout << "A != C : " << (ft_a != ft_c) << std::endl;
    std::cout << "A < B : " << (ft_a < ft_b) << std::endl;
    std::cout << "A < C : " << (ft_a < ft_c) << std::endl;
    std::cout << "A <= B : " << (ft_a <= ft_b) << std::endl;
    std::cout << "A <= C : " << (ft_a <= ft_c) << std::endl;
    std::cout << "A > B : " << (ft_a > ft_b) << std::endl;
    std::cout << "A > C : " << (ft_a > ft_c) << std::endl;
    std::cout << "A >= B : " << (ft_a >= ft_b) << std::endl;
    std::cout << "A >= C : " << (ft_a >= ft_c) << std::endl;
}