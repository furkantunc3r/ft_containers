#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"
#include <iterator>


namespace ft
{
    template<typename _Iterator>
    class reverse_iterator 
     : public std::iterator<typename ft::iterator_traits<_Iterator>::iterator_category,
                typename ft::iterator_traits<_Iterator>::value_type,
                typename ft::iterator_traits<_Iterator>::difference_type,
                typename ft::iterator_traits<_Iterator>::pointer,
                typename ft::iterator_traits<_Iterator>::reference>
    {
        protected :
        _Iterator current;

        public:
        typedef _Iterator													iterator_type;
        typedef typename ft::iterator_traits<_Iterator>::difference_type	difference_type;
        typedef typename ft::iterator_traits<_Iterator>::pointer			pointer;
        typedef typename ft::iterator_traits<_Iterator>::reference			reference;

        reverse_iterator() : current() { }
        explicit reverse_iterator(iterator_type __x) : current(__x) { }
        reverse_iterator(const reverse_iterator& __x) : current(__x.current) { }

        template<typename _Iter>
        reverse_iterator(const reverse_iterator<_Iter>& __x) : current(__x.base()) { }

        iterator_type base() const { return this->current; }
        
        reference operator*() const 
        {
            _Iterator __tmp = current;
            return *--__tmp;
        }
        pointer operator->() const { return &(operator*()); }
        reverse_iterator& operator++()
        {
            --current;
            return *this;
        }
        reverse_iterator operator++(int)
        {
            reverse_iterator __tmp = *this;
            --current;
            return __tmp;
        }
        reverse_iterator& operator--()
        {
            ++current;
            return *this;
        }
        reverse_iterator operator--(int)
        {
            reverse_iterator __tmp = *this;
            ++current;
            return __tmp;
        }
        reverse_iterator operator+(difference_type __n) const { return reverse_iterator(current - __n); }
        reverse_iterator& operator+=(difference_type __n)
        {
            current -= __n;
            return *this;
        }
        reverse_iterator operator-(difference_type __n) const { return reverse_iterator(current + __n); }
        reverse_iterator& operator -=(difference_type __n)
        {
            current += __n;
            return *this;
        }
        reference operator[](difference_type __n) const { return *(*this + __n); }
    };

  template< class Iterator1, class Iterator2 > bool operator==( const reverse_iterator<Iterator1>& lhs,
    const reverse_iterator<Iterator2>& rhs ){return lhs.base() == rhs.base();}//

	template< class Iterator1, class Iterator2 > bool operator!=( const reverse_iterator<Iterator1>& lhs,
    const reverse_iterator<Iterator2>& rhs ){return !(lhs == rhs);}//

	template< class Iterator1, class Iterator2 >bool operator<( const reverse_iterator<Iterator1>& lhs,
    const reverse_iterator<Iterator2>& rhs ){return rhs.base() < lhs.base();}//

	template< class Iterator1, class Iterator2 >bool operator<=( const reverse_iterator<Iterator1>& lhs,
    const reverse_iterator<Iterator2>& rhs ){ return !(rhs < lhs);}//

	template< class Iterator1, class Iterator2 >bool operator>( const reverse_iterator<Iterator1>& lhs,
    const reverse_iterator<Iterator2>& rhs ){return rhs < lhs;}//

	template< class Iterator1, class Iterator2 >bool operator>=( const reverse_iterator<Iterator1>& lhs,
    const reverse_iterator<Iterator2>& rhs ){return !(lhs < rhs);}//

	template<typename Iter> reverse_iterator<Iter>
	operator+( typename reverse_iterator<Iter>::difference_type n,
    const reverse_iterator<Iter>& it ){return reverse_iterator<Iter>(it.base() - n);}

	template<typename _Iterator> typename reverse_iterator<_Iterator>::difference_type
     operator-(const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator>& __y)
     { return __y.base() - __x.base(); }
}
#endif