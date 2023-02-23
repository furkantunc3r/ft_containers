#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include "./rb_tree/rb_tree.hpp"
#include "./rb_tree/pair.hpp"

namespace ft
{
    template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
    class set
    {
    public:
        typedef Key                                 key_type;
        typedef Key                                 value_type;
        typedef size_t                              size_type;
        typedef std::ptrdiff_t                      difference_type;
        typedef Compare                             key_compare;
        typedef Compare                             value_compare;
        typedef Allocator                           allocator_type;
        typedef value_type                          &reference;
        typedef const value_type                    &const_reference;
        typedef typename Allocator::pointer          pointer;
        typedef typename Allocator::const_pointer    const_pointer;

        typedef typename Allocator::template rebind<value_type>::other		allocator_value_type;
        typedef ft::rb_tree<value_type, value_compare, allocator_type>      _rep_type;
        
        _rep_type   _rb_t;

        typedef typename _rep_type::_Base_ptr                           _Base_ptr;
        typedef typename _rep_type::iterator                            iterator;
        typedef typename _rep_type::const_iterator                      const_iterator;
        typedef typename _rep_type::reverse_iterator                    reverse_iterator;
        typedef typename _rep_type::const_reverse_iterator              const_reverse_iterator;


        set() : _rb_t(key_compare(), allocator_type()) { }

        explicit set(const Compare& comp, const Allocator& alloc = Allocator()) : _rb_t(comp, allocator_type(alloc)) { }

        template<typename InputIt>
        set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : _rb_t(comp, alloc)
        {
            while (first != last)
            {
                _rb_t.insert(*first);
                ++first;
            }
        }

        set(const set& other) : _rb_t(other._rb_t) { }

        set& operator=(const set& other)
        {
            this->_rb_t = other._rb_t;
            return *this;
        }

        ~set() { }

        allocator_type get_allocator() const { return this->_rb_t._allocator; }

        iterator begin() { return _rb_t.begin(); }
        const_iterator begin() const { return _rb_t.begin(); }
        reverse_iterator rbegin() { return _rb_t.rbegin(); }
        const_reverse_iterator rbegin() const { return _rb_t.rbegin(); }

        iterator end() { return _rb_t.end(); }
        const_iterator end() const { return _rb_t.end(); }
        reverse_iterator rend() { return _rb_t.rend(); }
        const_reverse_iterator rend() const { return _rb_t.rend(); }

        bool empty() const { return _rb_t.empty(); }

        size_type size() const { return _rb_t._count; }

        size_type max_size() const { return _rb_t._allocator.max_size(); }

        ft::pair<iterator, bool>
        insert(const value_type& value)
        {
            int exists = 0;
            _Base_ptr pos = this->_rb_t.search(&exists, value);
            if (!exists)
            {
                _Base_ptr _new = _rb_t.insert_at(pos, value);
                return ft::pair<iterator, bool>(iterator(_new), true);
            }

            return ft::pair<iterator, bool>(iterator(pos), false);
        }

        iterator insert(iterator pos, const value_type& value)
        {
            if (pos == end())
                insert(value);
            else
                _rb_t.insert(pos._M_node, value);
            return lower_bound(value);
        }

        template<class InputIt>
        void insert(InputIt first, InputIt last)
        {
            while (first != last)
            {
                _rb_t.insert(*first);
                first++;
            }
        }

        void erase(iterator pos)
        { 
            if (size() != 0)
                _rb_t.deleteByVal(pos._M_node);
        }

        void erase(iterator first, iterator last)
        {
            iterator temp;
            while (first != last)
            {
                temp = first;
                first++;
                _rb_t.deleteByVal(temp._M_node);
            }
        }

        size_type erase(const value_type& value)
        {
            _Base_ptr _tmp = _rb_t.search(value);

            if (_tmp)
            {
                _rb_t.deleteByVal(_tmp);
                return 1;
            }
            return 0;
        }

        void swap(set& other)
        {
            std::swap(this->_rb_t._root, other._rb_t._root);
            std::swap(this->_rb_t._end, other._rb_t._end);
            std::swap(this->_rb_t._count, other._rb_t._count);
            std::swap(this->_rb_t._key_compare, other._rb_t._key_compare);
            std::swap(this->_rb_t._allocator, other._rb_t._allocator);
        }

        void clear() { _rb_t.clear(); }

        key_compare key_comp() const { return key_compare();}

        value_compare value_comp() const { return value_compare(key_compare()); }

        iterator find(const value_type& value)
        {
            _Base_ptr _tmp = _rb_t.search(value);

            if (_tmp)
                return iterator(_tmp);
            return iterator(_rb_t._end);
        }

        const_iterator find(const value_type& value) const
        {
            _Base_ptr _tmp = _rb_t.search(value);

            if (_tmp)
                return const_iterator(_tmp);
            return const_iterator(_rb_t._end);
        }

        size_type count(const value_type& value) const
        {
            _Base_ptr _tmp = _rb_t.search(value);

            if (_tmp)
                return 1;
            return 0;
        }

        iterator lower_bound(const value_type& value)
        {
            return _rb_t.lower_bound(value);
        }

        const_iterator lower_bound(const value_type& value) const
        {
            return _rb_t.lower_bound(value);
        }

        iterator upper_bound(const value_type& value)
        {
            return _rb_t.upper_bound(value);
        }

        const_iterator upper_bound(const value_type& value) const
        {
            return _rb_t.upper_bound(value);
        }

        ft::pair<iterator, iterator> equal_range(const value_type& value)
        {
            return (ft::make_pair(iterator(lower_bound(value)), iterator(upper_bound(value))));
        }

        ft::pair<const_iterator, const_iterator> equal_range(const value_type& value) const
        {
            return (ft::make_pair(const_iterator(lower_bound(value)), const_iterator(upper_bound(value))));
        }
    };

    template<class Key, class Compare, class Alloc>
    bool operator==(const set<Key, Compare, Alloc>&lhs, const set<Key, Compare, Alloc>& rhs)
    { return lhs._rb_t == rhs._rb_t; }
    
    template<class Key, class Compare, class Alloc>
    bool operator!=(const set<Key, Compare, Alloc>&lhs, const set<Key, Compare, Alloc>& rhs)
    { return (!(lhs == rhs)); }

    template<class Key, class Compare, class Alloc>
    bool operator<(const set<Key, Compare, Alloc>&lhs, const set<Key, Compare, Alloc>& rhs)
    { return lhs._rb_t < rhs._rb_t; }

    template<class Key, class Compare, class Alloc>
    bool operator<=(const set<Key, Compare, Alloc>&lhs, const set<Key, Compare, Alloc>& rhs)
    { return (!(rhs < lhs)); }

    template<class Key, class Compare, class Alloc>
    bool operator>(const set<Key, Compare, Alloc>&lhs, const set<Key, Compare, Alloc>& rhs)
    { return rhs < lhs; }

    template<class Key, class Compare, class Alloc>
    bool operator>=(const set<Key, Compare, Alloc>&lhs, const set<Key, Compare, Alloc>& rhs)
    { return (!(lhs < rhs)); }

    template<class Key, class Compare, class Alloc>
    void swap(set<Key, Compare, Alloc>& lhs, set<Key, Compare, Alloc>& rhs)
    { lhs.swap(rhs); }
};

#endif