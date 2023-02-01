#include "rb_tree.hpp"
#include <iostream>

int main()
{
    ft::rb_tree<int, std::less<int>, std::allocator<int>> tree;
    
    tree.insert(50);
    tree.insert(60);
    tree.insert(40);
    tree.insert(55);
    tree.insert(65);
    tree.insert(30);
    tree.insert(35);

    


    return 0;
}