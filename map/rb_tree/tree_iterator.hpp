#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "rb_tree.hpp"
#include "../../iterator_traits.hpp"

namespace ft
{
    template<typename _Tp>
    struct tree_iterator
    {
        typedef _Tp                             value_type;
        typedef _Tp&                            reference;
        typedef _Tp*                            pointer;

        typedef std::ptrdiff_t                  difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        
        typedef tree_iterator<_Tp>              _Self;
        typedef typename Node<_Tp>::_Base_ptr   _Base_ptr;
        typedef Node<_Tp>*                      _Link_type;

        _Base_ptr   _M_node;

        tree_iterator() : _M_node() { }

        explicit tree_iterator(const _Base_ptr _x) : _M_node(_x) { }

        reference operator*() const { return static_cast<_Link_type>(_M_node)->data; }

        pointer operator->() const { return &_M_node->data; }

        _Self& operator++()
        {
            _M_node = tree_increment(_M_node);
            return *this;
        }

        _Self operator++(int)
        {
            _Self _temp = *this;
            _M_node = tree_increment(_M_node);
            return _temp;
        }

        _Self& operator--()
        {
            _M_node = tree_decrement(_M_node);
            return *this;
        }

        _Self operator--(int)
        {
            _Self _temp = *this;
            _M_node = tree_decrement(_M_node);
            return _temp;
        }

        bool operator!=(const _Self &_x) const
        {
            return _x._M_node != _M_node;
        }

        bool operator==(const _Self &_x) const
        {
            return _x._M_node == _M_node;
        }

        const _Base_ptr& base() const { return _M_node; }
    };

    template<typename _Tp>
    struct const_tree_iterator
    {
        typedef _Tp                                         value_type;
        typedef const _Tp&                                  reference;
        typedef const _Tp*                                  pointer;

        typedef std::ptrdiff_t                              difference_type;
        typedef std::bidirectional_iterator_tag             iterator_category;
        typedef tree_iterator<value_type>                   iterator;

        typedef const_tree_iterator<value_type>             _Self;
        typedef typename Node<value_type>::_Const_Base_ptr  _Base_ptr;
        typedef const Node<_Tp>*                            _Link_type;

        _Base_ptr _M_node;

        const_tree_iterator() : _M_node() { }

        explicit const_tree_iterator(_Base_ptr _x) : _M_node(_x) { }

        const_tree_iterator(const iterator& _it) : _M_node(_it._M_node) { }

        reference operator*() const { return _M_node->data; }

        pointer operator->() const { return &_M_node->data; }

        _Self& operator++()
        {
            _M_node = tree_increment(_M_node);
            return *this;
        }

        _Self operator++(int)
        {
            _Self _temp = *this;
            _M_node = tree_increment(_M_node);
            return _temp;
        }

        _Self& operator--()
        {
            _M_node = tree_decrement(_M_node);
            return *this;
        }

        _Self operator--(int)
        {
            _Self _temp = *this;
            _M_node = tree_decrement(_M_node);
            return _temp;
        }

        bool operator!=(const _Self &_x) const
        {
            return _x._M_node != _M_node;
        }

        bool operator==(const _Self &_x) const
        {
            return _x._M_node == _M_node;
        }

        const _Base_ptr& base() const { return _M_node; }
    };

    template<typename _T> bool operator==(const tree_iterator<_T>& _x, const const_tree_iterator<_T>& _y)
    { return _x._M_node == _y._M_node; }

    template<typename _T> bool operator!=(const tree_iterator<_T>& _x, const const_tree_iterator<_T>& _y)
    { return _x._M_node != _y._M_node; }
};

#endif