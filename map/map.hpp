#include "rb_tree/rb_tree.hpp"
#include "pair.hpp"
#include <iostream>

namespace ft
{
    template <
        class Key,
        class T,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<ft::pair<const Key, T>>>
    class map
    {
        typedef Key                                                     key_type;
        typedef T                                                       mapped_type;
        typedef ft::pair<const Key, T>                                  value_type;
        typedef size_t                                                  size_type;
        typedef std::ptrdiff_t                                          difference_type;
        typedef Compare                                                 key_compare;
        typedef Allocator                                               allocator_type;
        typedef value_type                                              &reference;
        typedef const value_type                                        &const_reference;
        typedef allocator_type::pointer                                 pointer;
        typedef allocator_type::const_pointer                           const_pointer;
        typedef ft::rb_tree<value_type, value_compare, allocator_type>  _rep_type;
        
        typedef typename _rep_type::_Base_ptr                           _Base_ptr;
        typedef typename _rep_type::iterator                            iterator;
        typedef typename _rep_type::const_iterator                      const_iterator;
        typedef typename _rep_type::reverse_iterator                    reverse_iterator;
        typedef typename _rep_type::const_reverse_iterator              const_reverse_iterator;

        typedef typename Allocator::template rebind<value_type>::other  allocator_value_type;
        _rep_type                                                       _rb_t;

        class value_compare : public std::binary_function<value_type, value_type, bool>
        {
            friend class        map<Key, T, Compare, Allocator>;
            typedef bool        result_type;
            typedef value_type  first_argument_type;
            typedef value_type  second_argument_type;

        protected:
            Compare comp;

            value_compare(Compare c) : comp(c) {}

            bool operator()(const value_type &lhs, const value_type &rhs) const
            {
                return comp(lhs.first, rhs.first);
            }
        };

        map() : _rb_t(key_compare(), allocator_type()) { }

        explicit map(const Compare& comp, const Allacotar& alloc = Allocator()) : _rb_t(comp, allocator_value_type(alloc)) { }

        template<typename InputIt>
        map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : _rb_t(comp, alloc)
        {
            while (first != last)
            {
                _rb_t.insert(*first);
                ++first;
            }
        }

        map(const map& other) : _rb_t(other._rb_t) { }

        ~map() { }

        map& operator=(const map& other)
        {
            this->_rb_t = other._rb_t;
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

        mapped_type& operator[]( const key_type& key )
        {
            iterator i = iterator(lower_bound(key));
            if (i == end() || key_compare()(key, (i).first))
                i = insert(i, ft::make_pair(key, mapped_type()));
            return (i).second;
        }

        iterator begin() { return _rb_t.begin(); }
        const_iterator begin() const { return _rb_t.begin(); }
        reverse_iterator rbegin() { return _rb_t.rbegin(); }
        const_reverse_iterator rbegin() { return _rb_t.rbegin(); }
        
        iterator end() { return _rb_t.end(); }
        const_iterator end() const { return _rb_t.end(); }
        reverse_iterator rend() { return _rb_t.rend(); }
        const_reverse_iterator rend() { return _rb_t.rend(); }

        bool empty() const { return _rb_t.empty(); }

        size_type size() const { return _rb_t._count; }

        size_type max_size() const { return _rb_t._allocator.max_size(); }

        void clear() { _rb_t._m_erase(); }

        ft::pair<iterator, bool> insert(const value_type& value)
        {
            _Base_ptr _tmp = _rb_t.insert(value);

            if (_tmp)
                return ft::make_pair<iterator(_tmp), 1>;
            return ft::make_pair<iterator(_tmp), 0>;
        }

        iterator insert(iterator pos, const value_type& value)
        {
            iterator _it = _rb_t.insert(pos, value);
            return _it;
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

        void erase(iterator pos) { _rb_t.deleteByVal(*this); }
        
        void erase(iterator first, iterator last)
        {
            while (first != last)
            {
                _rb_t.deleteByVal(*first);
                first++;
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

        size_type count(const Key& key)
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
            
        }
    };
};