#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

namespace ft
{
    template <typename _Tp, typename _Alloc = std::allocator<_Tp> >
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

            allocator_type _allocator;
            pointer _begin;
            pointer _end;
            pointer _end_of_storage;

            vector() ;
            explicit vector (const allocator_type& alloc) : _allocator(alloc) {};
            explicit vector (size_type n, const _Tp& value = _Tp(), const allocator_type& alloc = allocator_type()) : _allocator(alloc)
            {
                this->_begin = this->_allocator.allocate(n);
                this->_end = this->_begin;
                for (int i = 0; i < n; i++)
                {
                    this->_allocator.construct(_end, value);
                    _end++;
                }
                this->_end_of_storage = this->_begin + n;
            }
    };
}

#endif