#ifndef RB_TREE_UTILS_HPP
#define RB_TREE_UTILS_HPP

#include <iostream>

namespace ft
{
    template<typename T>
    struct Node
    {
        typedef Node<T>*         _Base_ptr;
        typedef const Node<T>*   _Const_Base_ptr;

        T           data;
        _Base_ptr   parent;
        _Base_ptr   left;
        _Base_ptr   right;
        int         color; // 1 -> Red, 0 -> Black

        Node() : data(), color(0), left(), right(), parent() { }

        Node(const T &_value, _Base_ptr left = NULL, _Base_ptr right = NULL, _Base_ptr parent = NULL)
                : data(_value), color(1), left(left), right(right), parent(parent) { }

    };


};

#endif