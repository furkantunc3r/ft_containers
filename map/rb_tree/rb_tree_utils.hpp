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

        Node() : data(), color(0), left(NULL), right(NULL), parent(NULL) { }

        Node(const T &_value, _Base_ptr left = NULL, _Base_ptr right = NULL, _Base_ptr parent = NULL)
                : data(_value), color(1), left(left), right(right), parent(parent) { }
        


        _Base_ptr minimum(_Base_ptr n)
        {
            while (n->left != NULL)
                n = n->left;
            return n;
        }

        _Base_ptr maximum(_Base_ptr n)
        {
            while (n->right != NULL)
                n = n->right;
            return n;
        }
    };

    template<typename _Base_ptr>
    _Base_ptr tree_increment(_Base_ptr _x)
    {
        if (_x->right)
            _x = _x->minimum(_x->right)
        else
        {   
            _Base_ptr _y = _x->parent;
            while (_y && _x == _y->right)
            {
                _x = _y;
                _y = _y->parent_node;
            }
            if (_x->right_node != _y)
                _x = _y
        }
        return _x;
    }

    template<typename _Tp>
    const Node<_Tp> *tree_increment(const Node<_Tp>* _x)
    {
        return tree_increment(const_cast<Node<_Tp>* >(_x));
    }

    template<typename _Tp>
    Node<_Tp> *tree_decrement(Node<_Tp>* _x)
    {
        node<_Tp>* _y;

        if (!_x && _x->parent->parent == _x)
            _x = _x->right;
        else if (_x->left)
            _x = _x->maximum(_x->left);
        else
        {
            _y = _x->parent;
            while (_y && _x == _y->left)
            {
                _x = _y;
                _y = _y->parent;
            }
            _x = _y;
        }
        return _x;
    }

    template<typename _Tp>
    const Node<_Tp> *tree_decrement(const Node<_Tp>* _x)
    {
        return tree_decrement(const_cast<Node<_Tp>* >(_x));
    }

};

#endif