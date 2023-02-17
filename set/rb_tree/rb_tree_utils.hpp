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

        Node() : data(), parent(NULL), left(NULL), right(NULL), color(0) { }

        Node(const T &_value, _Base_ptr left = NULL, _Base_ptr right = NULL, _Base_ptr parent = NULL)
                : data(_value), parent(parent), left(left), right(right), color(1) { }
        
        _Base_ptr minimum(_Base_ptr n)
        {
            while (n && n->left != NULL)
                n = n->left;
            return n;
        }

        _Base_ptr maximum(_Base_ptr n)
        {
            while (n && n->right != NULL)
                n = n->right;
            return n;
        }
    };

    template<typename _Base_ptr>
    _Base_ptr tree_increment(_Base_ptr _x)
    {
        if (_x->right)
            _x = _x->minimum(_x->right);
        else
        {   
            _Base_ptr _y = _x->parent;
            while (_y && _x == _y->right)
            {
                _x = _y;
                _y = _y->parent;
            }
            if (_x->right != _y)
                _x = _y;
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
        Node<_Tp>* _y;

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

    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        while (first1!=last1)
        {
          if (first2==last2 || *first2<*first1) return false;
          else if (*first1<*first2) return true;
          ++first1; ++first2;
        }
        return (first2!=last2);
    }

    template <class InputIterator1, class InputIterator2>
    bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
    {
      while (first1!=last1) {
        if (!(*first1 == *first2))
          return false;
        ++first1; ++first2;
      }
      return true;
    }

    template<typename _Base_ptr, typename _Value, typename _Alloc>
    void create_node(_Base_ptr *_node, _Value _value, _Alloc _allocator)
    {
        *_node = _allocator.allocate(1);
        _allocator.construct(*_node, _value);
    }

    template<typename _Base_ptr, typename _Alloc>
    _Base_ptr copy(_Base_ptr tree, _Base_ptr first, _Base_ptr parent, _Alloc _alloc)
    {
        if (!first)
            return tree;
        create_node(&tree, first->data, _alloc);
        tree->parent = parent;
        tree->left = copy(tree->left, first->left, tree, _alloc);
        tree->right = copy(tree->right, first->right, tree, _alloc);
        return tree;
    }
};

#endif