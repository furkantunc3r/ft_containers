#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "normal_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
    template < typename _Tp, typename _Alloc = std::allocator<_Tp> >
    class vector
    {
        public :
            typedef _Tp value_type;
            typedef _Alloc allocator_type;
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef typename _Alloc::pointer pointer;
            typedef typename _Alloc::const_pointer const_pointer;
            typedef ft::normal_iterator<pointer, vector> iterator;
            typedef ft::normal_iterator<const_pointer, vector> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

            allocator_type _allocator;
            pointer _begin;
            pointer _end;
            pointer _end_of_storage;

            vector() : _begin(0), _end(0), _end_of_storage(0) {};
            explicit vector (const allocator_type& alloc) : _allocator(alloc) {};
            explicit vector (size_type n, const _Tp& value = _Tp(), const allocator_type& alloc = allocator_type()) : _allocator(alloc)
            {
                this->_begin = this->_allocator.allocate(n);
                this->_end = this->_begin;
                for (size_type i = 0; i < n; i++)
                {
                    this->_allocator.construct(_end, value);
                    _end++;
                }
                this->_end_of_storage = this->_begin + n;
            }
            template<class InputIt>
            vector (InputIt first, InputIt last, const allocator_type& alloc = allocator_type()) : _allocator(alloc)
            {
                size_type i = 0;
                for (InputIt temp = first; temp != last; temp++)
                    i++;
                this->_begin = this->_allocator.allocate(i);
                this->_end = this->_begin;
                while (first != last)
                {
                    this->_allocator.construct(_end, *first);
                    first++;
                    _end++;
                }
                this->_end_of_storage = this->_begin + i;
            }
            vector (const vector& other) : _allocator(other._allocator)
            {
                this->_begin = this->_allocator(other.capacity());
                this->_end = this->_begin;
                this->_end_of_storage = this->_begin + (other.capacity());
                for (pointer _temp = other->_begin; _temp != other->_end; _temp++)
                {
                    this->_allocator.construct(_end, _temp);
                    _end++;
                }
            }
            ~vector() {};
            vector& operator= (const vector& other)
            {
                for (pointer _temp = this->_begin; _temp <= this->_end_of_storage; _temp++)
                    this->_allocator.destroy(_temp);
                this->_allocator.deallocate(this->_begin, capacity());
                this->_begin = this->_allocator.allocate(other.capacity());
                this->_end = this->_begin;
                for (pointer _tempOther = other._begin; _tempOther <= other._end_of_storage; _tempOther++)
                {
                    this->_allocator.construct(_end, _tempOther);
                    _end++;
                }
                this->_end_of_storage = this->_begin + (other.capacity());
                return *this;
            }
            void assign(size_type count, const _Tp& value)
            {
                clear();
                if (count > this->capacity())
                {
                    if (capacity())
                        this->_allocator.deallocate(this->_begin, capacity());
                    this->_begin = this->_allocator.allocate(count);
                    this->_end = this->_begin;
                }
                for (size_type i = 0; i < count; i++)
                {
                    this->_allocator.construct(_end, value);
                    _end++;
                }
                this->_end_of_storage = this->_end + count;
            }
            template<class InputIt>
            void assign(InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value, bool>::type = true)
            {
                size_type _count = last - first;
                clear();
                if (_count > capacity())
                {
                    if (capacity())
                        this->_allocator.deallocate(this->_begin, capacity());
                    this->_begin = this->_allocator.allocate(_count);
                    this->_end = this->_begin;
                }
                for (; first != last; first++)
                {
                    this->_allocator.construct(_end, *first);
                    _end++;
                }
                this->_end_of_storage = this->_end + _count;
            }
            allocator_type get_allocator() const { return this->_allocator; }
            
            // element access

            reference at(size_type pos)
            {
                if (pos > capacity())
                    throw std::out_of_range("Out of bounds!");
                return reference(this->_begin[pos]);
            };
            const_reference at(size_type pos) const
            {
                if (pos > capacity())
                    throw std::out_of_range("Out of bounds!");
                return const_reference(this->_begin[pos]);
            };

            reference operator[] (size_type pos) { return reference(this->_begin[pos]); }
            const_reference operator[] (size_type pos) const { return const_reference(this->_begin + pos); }

            reference front() { return reference(*this->_begin); }
            const_reference front() const { return const_reference(*this->_begin); }

            reference back() { return reference(*(this->_end - 1)); }
            const_reference back() const { return const_reference(*(this->_end - 1)); }

            _Tp* data() { return pointer(this->_begin); }
            const _Tp* data() const { return const_pointer(this->_begin); }

            // iterator

            iterator begin() { return iterator(this->_begin); }
            const_iterator begin() const { return const_iterator(this->_begin); }
            iterator end() { return iterator(this->_end); }
            const_iterator end() const { return const_iterator(this->_end); }

            reverse_iterator rbegin() { return reverse_iterator(end()); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
            reverse_iterator rend() { return reverse_iterator(begin()); }
            const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

            // capacity

            bool empty() const
            {
                if (this->_begin == this->_end)
                    return 1;
                return 0;
            }
            size_type size() const { return size_type(this->_end - this->_begin); }
            size_type max_size() const { return this->_allocator.max_size(); }
            void reserve (size_type new_cap)
            {
                if (new_cap > max_size())
                    throw std::length_error("Max size exceeded!");
                if (new_cap > capacity())
                {
                    pointer _temp = this->_allocator.allocate(new_cap);
                    size_type _size = size();
                    if (this->_begin)
                    {
                        for (size_type i = 0; i < _size; i++)
                        {
                            this->_allocator.construct(_temp + i, *(this->_begin + i));
                            this->_allocator.destroy(this->_begin + i);
                        }
                        this->_allocator.deallocate(this->_begin, capacity());
                        this->_begin = _temp;
                        this->_end = this->_begin + _size;
                        this->_end_of_storage = this->_begin + new_cap;
                    }
                    else
                    {
                        this->_begin = this->_allocator.allocate(new_cap);
                        this->_end = this->_begin;
                        this->_end_of_storage = this->_begin + new_cap;
                    }
                }
            }
            size_type capacity() const { return size_type(this->_end_of_storage - this->_begin); }

            // modifiers

            void clear()
            {
                size_type _size = size();
                for (size_type _i = 0; _i < _size; _i++)
                    this->_allocator.destroy(this->_begin + _i);
                this->_end = this->_begin;
            }
            iterator insert(iterator pos, const value_type& value)
            {
                if (capacity() != size() && pos == end())
                {
                    this->_allocator.construct(this->_end, value);
                    _end++;
                    return pos;
                }
                else
                {
                    if (this->_end != this->_end_of_storage)
                    {
                        pointer _tmp;
                        size_type _size = size();
                        size_type _cap = capacity();
                        size_type j = 0;
                        _tmp = this->_allocator.allocate(capacity());
                        for (size_type i = 0; i < _size; i++)
                        {
                            this->_allocator.construct(_tmp, *(this->_begin + i));
                            _tmp++;
                        }
                        _tmp -= _size;
                        clear();
                        for (size_type i = 0; i <= _size; i++)
                        {
                            if ((pos - begin()) == (long int)i)
                            {
                                this->_allocator.construct(&(this->_begin[i]), value);
                                j -= 1;
                            }
                            else
                                this->_allocator.construct(&(this->_begin[i]), _tmp[j]);
                            this->_end++;
                            j++;
                        }
                        this->_end_of_storage = this->_begin + (_cap + 1);
                        return pos;
                    }
                    else
                    {
                        this->reserve(capacity() + 1);
                        pointer _tmp;
                        size_type _size = size();
                        size_type _cap = capacity();
                        size_type j = 0;
                        _tmp = this->_allocator.allocate(capacity());
                        for (size_type i = 0; i < _size; i++)
                        {
                            this->_allocator.construct(_tmp, *(this->_begin + i));
                            _tmp++;
                        }
                        _tmp -= _size;
                        clear();
                        for (size_type i = 0; i <= _size; i++)
                        {
                            if ((pos - begin()) == (long int)i) // fix the need for typecast
                            {
                                this->_allocator.construct(&(this->_begin[i]), value);
                                j -= 1;
                            }
                            else
                                this->_allocator.construct(&(this->_begin[i]), _tmp[j]);
                            this->_end++;
                            j++;
                        }
                        this->_end_of_storage = this->_begin + (_cap + 1);
                        return pos;
                    }
                }
            }
            iterator insert(iterator pos, size_type count, const value_type& value) // check const_iterator to iterator issue
            {
                for (size_type i = 0; i < count; i++)
                    insert(pos, value);
                return pos;
            }
            template<class InputIt>
            iterator insert(iterator pos, InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value, bool>::type = true)
            {
                for (; first != last; ++first)
                    pos = insert(pos, *first);
                return pos;
            }
            iterator erase (iterator pos)
            {
                pointer _tmp;
                size_type _size = size();
                _tmp = this->_allocator.allocate(capacity());
                for (size_type i = 0; i < _size; i++)
                {
                    this->_allocator.construct(_tmp, *(this->_begin + i));
                    _tmp++;
                }
                _tmp -= _size;
                clear();
                for (size_type i = 0; i < _size - 1; i++)
                {
                    if ((pos - begin()) == (long int)i)
                        _tmp++;
                    else
                    {
                        this->_allocator.construct(this->_begin + i, *_tmp);
                        _tmp++;
                        this->_end++;
                    }
                }
                return pos;
            }
            iterator erase (iterator first, iterator last)
            {
                while (first != last)
                {
                    erase(first);
                    first++;
                }
                return first;
            }
            void push_back (const _Tp& value)
            {
                insert(end(), value);
            }
            void pop_back ()
            {
                erase(end());
            }
            void resize(size_type count, _Tp value = _Tp())
            {
                if (size() > count)
                {
                    size_type i = end() - (begin() + count);
                    while (i > 0)
                    {
                        pop_back();
                        i--;
                    }
                }
                else if (size() < count)
                {
                    size_type _size = size();
                    while (_size < count)
                    {
                        push_back(value);
                        _size++;
                    }
                }
                else
                    return ;
            }
            void swap(vector& other)
            {
                std::swap(this->_begin, other._begin);
                std::swap(this->_end, other._end);
                std::swap(this->_end_of_storage, other._end_of_storage);     
            }
        };
};

template<class T, class Alloc>
bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
    if (lhs.size() != rhs.size())
        return 0;
    ft::vector<int>::const_iterator _l = lhs.begin();
    ft::vector<int>::const_iterator _lend = lhs.end();
    ft::vector<int>::const_iterator _r = rhs.begin();
    while (_l != _lend)
    {
        if (*_l != *_r)
            return 0;
        _l++;
        _r++;
    }
    return 1;
}

template<class T, class Alloc >
bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
    if (lhs.size() != rhs.size())
        return 1;
    ft::vector<int>::const_iterator _l = lhs.begin();
    ft::vector<int>::const_iterator _lend = lhs.end();
    ft::vector<int>::const_iterator _r = rhs.begin();
    while (_l != _lend)
    {
        if (*_l != *_r)
            return 1;
        _l++;
        _r++;
    }
    return 0;
}

template<class T, class Alloc>
bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
    if (lhs == rhs)
        return 0;
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<class T, class Alloc>
bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
    if (lhs == rhs && (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())))
        return 0;
    return 1;
}

template<class T, class Alloc>
bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
    if (lhs == rhs)
        return 0;
    return !(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template<class T, class Alloc>
bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
    if (lhs == rhs && !(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())))
        return 1;
    return 0;
}

#endif