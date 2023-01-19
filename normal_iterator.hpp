#ifndef NORMAL_ITERATOR_HPP
#define NORMAL_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"
#include "utils.hpp"

namespace ft
{
    template <typename _Iterator, typename _Container>
    class normal_iterator
    {
    protected:
        _Iterator current;
        typedef iterator_traits<_Iterator> _traits_type;

    public:
        typedef _Iterator iterator_type;
        typedef typename _traits_type::iterator_category iterator_category;
        typedef typename _traits_type::value_type value_type;
        typedef typename _traits_type::difference_type difference_type;
        typedef typename _traits_type::reference reference;
        typedef typename _traits_type::pointer pointer;
        
        normal_iterator() : current(_Iterator()) {}
        explicit normal_iterator(const _Iterator& __i) : current(__i) {}
        template<typename _Iter> normal_iterator(const normal_iterator<_Iter, 
                typename enable_if<
                (ft::__are_same<_Iter, typename _Container::pointer>::__value), 
                _Container>::__type>& __i)
            : current(__i.base()) { }

        // Forward operations
        reference operator*() const { return *current; }
        pointer operator->() const { return current; }
        normal_iterator &operator++()
        {
            ++current;
            return *this;
        }
        normal_iterator operator++(int) { return normal_iterator(current++); }
        // Bidirectional operations
        normal_iterator &operator--()
        {
            --current;
            return *this;
        }
        normal_iterator operator--(int) { return normal_iterator(current--); }
        // Random access operations
        reference operator[](const difference_type &_n) const { return current[_n]; }
        normal_iterator &operator+=(const difference_type &_n)
        {
            current += _n;
            return *this;
        }
        normal_iterator operator+(const difference_type &_n) const { return normal_iterator(current + _n); }
        normal_iterator &operator-=(const difference_type &_n)
        {
            current -= _n;
            return *this;
        }
        normal_iterator operator-=(const difference_type &_n) const { return normal_iterator(current - _n); }
        const _Iterator &base() const { return current; }
    };
    // Forward reqs
    template <typename _IteratorL, typename _IteratorR, typename _Container>
    bool operator==(const normal_iterator<_IteratorL, _Container> &__lhs,
                    const normal_iterator<_IteratorR, _Container> &__rhs)
    {
        return __lhs.base() == __rhs.base();
    }
    template <typename _IteratorL, typename _IteratorR, typename _Container>
    bool operator!=(const normal_iterator<_IteratorL, _Container> &__lhs,
                    const normal_iterator<_IteratorR, _Container> &__rhs)
    {
        return __lhs.base() != __rhs.base();
    }
    // Random access reqs
    template <typename _IteratorL, typename _IteratorR, typename _Container>
    bool operator<(const normal_iterator<_IteratorL, _Container> &__lhs,
                   const normal_iterator<_IteratorR, _Container> &__rhs)
    {
        return __lhs.base() < __rhs.base();
    }
    template <typename _IteratorL, typename _IteratorR, typename _Container>
    bool operator>(const normal_iterator<_IteratorL, _Container> &__lhs,
                   const normal_iterator<_IteratorR, _Container> &__rhs)
    {
        return __lhs.base() > __rhs.base();
    }
    template <typename _IteratorL, typename _IteratorR, typename _Container>
    bool operator<=(const normal_iterator<_IteratorL, _Container> &__lhs,
                    const normal_iterator<_IteratorR, _Container> &__rhs)
    {
        return __lhs.base() <= __rhs.base();
    }
    template <typename _IteratorL, typename _IteratorR, typename _Container>
    bool operator>=(const normal_iterator<_IteratorL, _Container> &__lhs,
                    const normal_iterator<_IteratorR, _Container> &__rhs)
    {
        return __lhs.base() >= __rhs.base();
    }
    template <typename _IteratorL, typename _IteratorR, typename _Container>
    typename normal_iterator<_IteratorL, _Container>::difference_type
    operator-(const normal_iterator<_IteratorL, _Container> &__lhs,
              const normal_iterator<_IteratorR, _Container> &__rhs) { return __lhs.base() - __rhs.base(); }
    template <typename _IteratorL, typename _IteratorR, typename _Container>
    typename normal_iterator<_IteratorL, _Container>::difference_type
    operator+(const normal_iterator<_IteratorL, _Container> &__lhs,
              const normal_iterator<_IteratorR, _Container> &__rhs) { return __lhs.base() + __rhs.base(); }
}
#endif