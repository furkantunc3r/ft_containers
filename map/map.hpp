#include "./rb_tree/rb_tree.hpp"
#include "./rb_tree/pair.hpp"
#include <iostream>

namespace ft
{
    template <
        class Key,
        class T,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
    public:
        typedef Key                                                     key_type;
        typedef T                                                       mapped_type;
        typedef ft::pair<const Key, T>                                  value_type;
        typedef size_t                                                  size_type;
        typedef std::ptrdiff_t                                          difference_type;
        typedef Compare                                                 key_compare;
        typedef Allocator                                               allocator_type;
        typedef value_type                                              &reference;
        typedef const value_type                                        &const_reference;
        typedef typename allocator_type::pointer                                 pointer;
        typedef typename allocator_type::const_pointer                           const_pointer;
        

        typedef typename Allocator::template rebind<value_type>::other  allocator_value_type;
        

        class value_compare : public std::binary_function<value_type, value_type, bool>
        {
            friend class        map<Key, T, Compare, Allocator>;
            typedef bool        result_type;
            typedef value_type  first_argument_type;
            typedef value_type  second_argument_type;

        protected:
            Compare comp;

            value_compare(Compare c) : comp(c) {}
            
        public:
            bool operator()(const value_type &lhs, const value_type &rhs) const
            {
                return comp(lhs.first, rhs.first);
            }
        };

        typedef ft::rb_tree<value_type, value_compare, allocator_type>  _rep_type;
        typedef typename _rep_type::_Base_ptr                           _Base_ptr;
        typedef typename _rep_type::iterator                            iterator;
        typedef typename _rep_type::const_iterator                      const_iterator;
        typedef typename _rep_type::reverse_iterator                    reverse_iterator;
        typedef typename _rep_type::const_reverse_iterator              const_reverse_iterator;

        _rep_type                                                       _rb_t;

        map() : _rb_t(key_compare(), allocator_type()) { }

        map(const map& other) : _rb_t(other._rb_t) { }

        explicit map(const Compare& comp, const Allocator& alloc = Allocator()) : _rb_t(comp, allocator_value_type(alloc)) { }

        template<typename InputIt>
        explicit map(InputIt first, InputIt last, const Compare comp = Compare(), const Allocator& alloc = Allocator()) : _rb_t(comp, alloc)
        {
            while (first != last)
            {
                _rb_t.insert(*first);
                ++first;
            }
        }

        ~map() { }

        map& operator=(const map& other)
        {
            this->_rb_t = other._rb_t;
            return *this;
        }

        allocator_type get_allocator() const { return this->_rb_t._allocator; }

        T& at(const Key& key)
        {
            _Base_ptr _tmp;

            _tmp = this->_rb_t.search(ft::make_pair(key, T()));
            if (!_tmp)
                throw std::out_of_range("No such element in map!");
            return _tmp->data.second;
        }

        const T& at(const Key& key) const
        {
            _Base_ptr _tmp;

            _tmp = this->_rb_t.search(ft::make_pair(key, T()));
            if (!_tmp)
                throw std::out_of_range("No such elemnt in map!");
            return _tmp->data.second;
        }

        mapped_type& operator[]( const key_type& key )
        {
            iterator i = iterator(lower_bound(key));
            if (i == end() || key_compare()(key, (*i).first))
                i = insert(i, ft::make_pair(key, mapped_type()));
            return (*i).second;
        }

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

        void clear() { _rb_t.clear(); }

        ft::pair<iterator, bool>
        insert(const value_type& value)
        {
            _Base_ptr ret = _rb_t.search(value);

            if (ret)
                return ft::pair<iterator, bool>(iterator(ret), false);
            else
                _rb_t.insert(value);
            return ft::pair<iterator, bool>(iterator(_rb_t.search(value)), true);
        }

        iterator insert(iterator pos, const value_type& value)
        {
            if (pos == end())
                insert(value);
            else
                _rb_t.insert(pos._M_node, value);
            return lower_bound(value.first);
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
                _rb_t.deleteByVal(pos._M_node->data);
        }
        
        void erase(iterator first, iterator last)
        {
            iterator temp;
            while (first != last)
            {
                temp = first;
                first++;
                _rb_t.deleteByVal(temp._M_node->data);
            }
        }

        size_type erase(const Key& key)
        {
            _Base_ptr _tmp = _rb_t.search(ft::make_pair(key, mapped_type()));
            
            if (_tmp)
            {
                _rb_t.deleteByVal(_tmp->data);
                return 1;
            }
            return 0;
        }

        void swap(map& other)
        {
            std::swap(this->_rb_t._root, other._rb_t._root);
            std::swap(this->_rb_t._end, other._rb_t._end);
            std::swap(this->_rb_t._count, other._rb_t._count);
            std::swap(this->_rb_t._key_compare, other._rb_t._key_compare);
            std::swap(this->_rb_t._allocator, other._rb_t._allocator);
        }

        size_type count(const Key& key) const
        {
            _Base_ptr _tmp = _rb_t.search(ft::make_pair(key, mapped_type()));

            if (_tmp)
                return 1;
            return 0;
        }

        iterator find(const Key& key)
        {
            _Base_ptr _tmp = _rb_t.search(ft::make_pair(key, mapped_type()));

            if (_tmp)
                return iterator(_tmp);
            return iterator(_rb_t._end);
        }

        const_iterator find(const Key& key) const
        {
            _Base_ptr _tmp = _rb_t.search(ft::make_pair(key, mapped_type()));

            if (_tmp)
                return const_iterator(_tmp);
            return const_iterator(_rb_t._end);
        }

        ft::pair<iterator, iterator> equal_range(const Key& key)
        {
            return (ft::make_pair(iterator(lower_bound(key)), iterator(upper_bound(key))));
        }

        ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
        {
            return (ft::make_pair(const_iterator(lower_bound(key)), const_iterator(upper_bound(key))));
        }

        iterator lower_bound(const Key& key)
        {
            return _rb_t.lower_bound(ft::make_pair(key, mapped_type()));
        }

        const_iterator lower_bound(const Key& key) const
        {
            return _rb_t.lower_bound(ft::make_pair(key, mapped_type()));
        }

        iterator upper_bound(const Key& key)
        {
            return _rb_t.upper_bound(ft::make_pair(key, mapped_type()));
        }

        const_iterator upper_bound(const Key& key) const
        {
            return _rb_t.upper_bound(ft::make_pair(key, mapped_type()));
        }

        key_compare key_comp() const { return key_compare(); }

        value_compare value_comp() const { return value_compare(key_compare()); }
    };

    template<class Key, class T, class Compare, class Alloc>
    bool operator==(const map<Key, T, Compare, Alloc>&lhs, const map<Key, T, Compare, Alloc>& rhs)
    { return lhs._rb_t == rhs._rb_t; }
    
    template<class Key, class T, class Compare, class Alloc>
    bool operator!=(const map<Key, T, Compare, Alloc>&lhs, const map<Key, T, Compare, Alloc>& rhs)
    { return (!(lhs == rhs)); }

    template<class Key, class T, class Compare, class Alloc>
    bool operator<(const map<Key, T, Compare, Alloc>&lhs, const map<Key, T, Compare, Alloc>& rhs)
    { return lhs._rb_t < rhs._rb_t; }

    template<class Key, class T, class Compare, class Alloc>
    bool operator<=(const map<Key, T, Compare, Alloc>&lhs, const map<Key, T, Compare, Alloc>& rhs)
    { return (!(rhs < lhs)); }

    template<class Key, class T, class Compare, class Alloc>
    bool operator>(const map<Key, T, Compare, Alloc>&lhs, const map<Key, T, Compare, Alloc>& rhs)
    { return rhs < lhs; }

    template<class Key, class T, class Compare, class Alloc>
    bool operator>=(const map<Key, T, Compare, Alloc>&lhs, const map<Key, T, Compare, Alloc>& rhs)
    { return (!(lhs < rhs)); }

    template<class Key, class T, class Compare, class Alloc>
    void swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs)
    { lhs.swap(rhs); }
};