#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cstddef>
#include "../normal_iterator.hpp"
#include "../reverse_iterator.hpp"

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

        private:
            template<class InputIt>
            void _insert(iterator pos, InputIt first, InputIt last, std::input_iterator_tag)
            {
                for(; first != last; first++, pos++)
                    pos = insert(pos, *first);
            }

            template<class randIt>
            void _insert(iterator pos, randIt first, randIt last, std::random_access_iterator_tag)
            {
                if (first == last)
                    return;
                size_type len = (last - first);
                size_type oldCap = capacity();
                size_type newCap = !oldCap ? len : oldCap;

                if ((size() + len) > newCap * 2)
                    newCap = size() + len;
                else if ((size() + len) > newCap)
                    newCap *= 2;
                pointer newData = this->_allocator.allocate(newCap);
                pointer newEnd = newData;
                
                for(iterator it = begin(); it != pos; it++, newEnd++)
                    this->_allocator.construct(newEnd, *it);
                for(; first != last; first++, newEnd++)
                    this->_allocator.construct(newEnd, *first);
                for(iterator it = pos; it != end(); it++, newEnd++)
                    this->_allocator.construct(newEnd, *it);
                if (oldCap)
                {
                    clear();
                    this->_allocator.deallocate(this->_begin, oldCap);
                }
                this->_begin = newData;
                this->_end = newEnd;
                this->_end_of_storage = this->_begin + newCap;
            }
        
        public:
            vector() : _begin(0), _end(0), _end_of_storage(0)
            {
                this->_begin = NULL;
                this->_end = this->_begin;
                this->_end_of_storage = this->_end;
            }

            explicit vector (const allocator_type& alloc) : _allocator(alloc)
            {
                this->_begin = NULL;
                this->_end = this->_begin;
                this->_end_of_storage = this->_end;
            }

            explicit vector (size_type n, const _Tp& value = _Tp(), const allocator_type& alloc = allocator_type()) : _allocator(alloc), _begin(0), _end(0), _end_of_storage(0)
            {
                if (n > max_size())
                    throw std::length_error("Length Error");
                if (n)
                {
                    this->_begin = this->_allocator.allocate(n);
                    this->_end = this->_begin;
                    this->_end_of_storage = this->_begin + n;
                    for (size_type i = 0; i < n; i++)
                    {
                        this->_allocator.construct(_end, value);
                        this->_end++;
                    }
                }
            }

            template<class InputIt> // CHANGED
            vector (InputIt first, InputIt last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!is_integral<InputIt>::value, bool>::type = true) : _allocator(alloc), _begin(0), _end(0), _end_of_storage(0)
            {
                assign(first, last);
                // size_type i = 0;
                // for (InputIt temp = first; temp != last; temp++)
                //     i++;
                // this->_begin = this->_allocator.allocate(i);
                // this->_end = this->_begin;
                // while (first != last)
                // {
                //     this->_allocator.construct(_end, *first);
                //     first++;
                //     _end++;
                // }
                // this->_end_of_storage = this->_begin + i;
            }

            vector (const vector& other) : _allocator(other._allocator)
            {
                this->_begin = this->_allocator.allocate(other.capacity());
                this->_end = this->_begin;
                this->_end_of_storage = this->_begin + (other.capacity());
                for (size_type it = 0; it < other.size(); it++)
                {
                    this->_allocator.construct(_end, other[it]);
                    _end++;
                }
            }

            ~vector()
            {
                if (capacity())
                {
                    clear();
                    this->_allocator.deallocate(this->_begin, capacity());
                }
            }

            vector& operator= (const vector& other)
            {
                if (this != &other)
                {
                    const size_type len = other.size();
                    if (len > capacity())
                    {
                        pointer temp_start = this->_allocator.allocate(len);
                        pointer temp_finish = temp_start;
                        for (size_type i = 0; i < other.size(); i++)
                        {
                            this->_allocator.construct(temp_finish, other[i]);
                            temp_finish++;
                        }
                        clear();
                        if (capacity())
                            this->_allocator.deallocate(this->_begin, capacity());
                        this->_begin = temp_start;
                        this->_end = temp_finish;
                        this->_end_of_storage = this->_begin + len;
                    }
                    else if (size() > len)
                    {
                        clear();
                        assign(other.begin(), other.end());
                    }
                    else if (capacity())
                        assign(other.begin(), other.end());
                }
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
                    this->_end_of_storage = this->_begin + count;
                }
                for (size_type i = 0; i < count; i++)
                {
                    this->_allocator.construct(_end, value);
                    _end++;
                }
            }

            template< class InputIterator > void assign( InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true)
			{
				typedef typename ft::iterator_traits<InputIterator>::iterator_category iter;
				if (ft::__are_same<iter, std::random_access_iterator_tag>::__value)
				{
					difference_type _len = std::distance(first, last);
					clear();
					if (_len > (difference_type)capacity())
					{
						if (capacity())
							this->_allocator.deallocate(this->_begin, capacity());
						this->_begin = this->_allocator.allocate(_len);
						this->_end = this->_begin;
						this->_end_of_storage = this->_begin + _len;
					}
					while(first != last)
					{
						this->_allocator.construct(this->_end, *first);
						first++;
						this->_end++;
					}	
				}
				else
				{
					iterator pos(begin());

					while ((pos != end()) && (first != last))
					{
						*pos = *first;
						++first;
						++pos;
					}
					if (first == last)
						erase(pos, end());
					else
						insert(end(), first, last);
				}
			}

            allocator_type get_allocator() const { return this->_allocator; }
            
            // element access

            reference at(size_type pos)
            {
                if (pos >= size())
                    throw std::out_of_range("Out of bounds!");
                return reference(this->_begin[pos]);
            };
            const_reference at(size_type pos) const
            {
                if (pos >= size())
                    throw std::out_of_range("Out of bounds!");
                return const_reference(this->_begin[pos]);
            };

            reference operator[] (size_type pos) { return reference(this->_begin[pos]); }
            const_reference operator[] (size_type pos) const { return const_reference(this->_begin[pos]); }

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

            bool empty() const { return begin() == end(); }

            size_type size() const { return size_type(this->_end - this->_begin); }

            size_type max_size() const { return this->_allocator.max_size(); }

            void reserve (size_type new_cap)
            {
                if (new_cap > max_size())
                    throw std::length_error("Max size exceeded!");
                if (new_cap > capacity())
                {
                    if (this->_begin)
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
                            if (capacity())
                                this->_allocator.deallocate(this->_begin, capacity());
                            this->_begin = _temp;
                            this->_end = this->_begin + _size;
                            this->_end_of_storage = this->_begin + new_cap;
                        }
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

           iterator insert(iterator pos, const _Tp& _value)
			{
				size_type _new_pos = size_type(pos - begin());
				if (this->_end != this->_end_of_storage && pos == end())
					this->_allocator.construct(this->_end++, _value);
				else if (size() + 1 < capacity())
				{
					size_type _pos = (end() - pos);
					this->_allocator.construct(this->_end++, _value);
					std::swap_ranges(rbegin(), rbegin() + _pos, rbegin() + 1);
				}
				else
				{
					size_type oldCap = capacity();
					size_type newSize = size() ? oldCap * 2 : 1;
					pointer newData = this->_allocator.allocate(newSize);
					pointer newEnd = newData;

					for(iterator it = begin(); it != pos; it++, newEnd++)
						this->_allocator.construct(newEnd, *it);
					this->_allocator.construct(newEnd++, _value);
					for(iterator it = pos; it != end(); it++, newEnd++)
						this->_allocator.construct(newEnd, *it);
					if (oldCap)
					{
						clear();
						this->_allocator.deallocate(this->_begin, oldCap);
					}
					this->_begin = newData;
					this->_end = newEnd;
					this->_end_of_storage = this->_begin + newSize;
				}
				return iterator(this->_begin + _new_pos);
			}

            iterator insert(iterator pos, size_type count, const value_type& value) //changed
            {
                size_type _new_pos = size_type(pos - begin());
                size_type len = end() - pos;

                if (count > max_size())
                    throw std::length_error("Length Error");
                if (count == 0)
                    return pos;
                if (size() + count > capacity())
                {
                    if (size() + count > capacity() * 2)
                        reserve(size() + count);
                    else
                        reserve(capacity() * 2);
                }
                for (size_type i = 0; i < count; i++)
                {
                    this->_allocator.construct(this->_end, value);
                    this->_end++;
                }
                std::swap_ranges(rbegin(), rbegin() + len, rbegin() + count);
                return iterator(this->_begin + _new_pos);

                // for (size_type i = 0; i < count; i++, pos++)
                //     pos = insert(pos, value);
                // return pos;
            }

            template<class InputIt>
            iterator insert(iterator pos, InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value, bool>::type = true)
            {
                typedef typename ft::iterator_traits<InputIt>::iterator_category iter;
                _insert(pos, first, last, iter());
                return pos;
            }

            iterator move(iterator first, iterator last, iterator result)
			{
				for(; first != last; ++result, ++first)
					*result = *first;
				return result;
			}

            iterator erase( iterator pos ) 
			{
				if (pos + 1 != end())
					move(pos + 1, end(), pos);
                this->_end--;
				this->_allocator.destroy(this->_end);
				return pos;
			}

            iterator erase(iterator first, iterator last) 
			{
				if (first != last)
				{
					size_type len = (last - first);
					if (last != end())
						move(last, end(), first);
					for (size_type i = 0; i < len; i++)
						pop_back();
				}
				return (first);
			}
            
            void push_back (const _Tp& value)
            {
                insert(end(), value);
            }
            void pop_back ()
            {
                erase(end() - 1);
            }
            void resize(size_type count, _Tp value = _Tp()) // changed
            {
                size_type _end = size();
                
                if (count > _end)
                    insert(end(), count - _end, value);
                else
                {
                    while (count < _end)
                    {
                        this->_allocator.destroy(this->_begin + count);
                        this->_end--;
                        count++;
                    }
                }
                // if (size() > count)
                // {
                //     size_type i = end() - (begin() + count);
                //     while (i > 0)
                //     {
                //         pop_back();
                //         i--;
                //     }
                // }
                // else if (size() < count)
                // {
                //     size_type _size = size();
                //     while (_size < count)
                //     {
                //         push_back(value);
                //         _size++;
                //     }
                // }
                // else
                //     return ;
            }
            void swap(vector& other)
            {
                std::swap(this->_begin, other._begin);
                std::swap(this->_end, other._end);
                std::swap(this->_end_of_storage, other._end_of_storage);     
            }
        };


    template<class T, class Alloc>
    bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template<class T, class Alloc >
    bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return (!(lhs == rhs));
    }

    template<class T, class Alloc>
    bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template<class T, class Alloc>
    bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return (!(rhs < lhs));
    }

    template<class T, class Alloc>
    bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return (rhs < lhs);
    }

    template<class T, class Alloc>
    bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return (!(lhs < rhs));
    }

    template<class T, class Alloc>
    void swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs)
    {
        lhs.swap(rhs);
    }

};

#endif