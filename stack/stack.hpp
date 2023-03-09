#ifndef STACK_HPP
#define STACK_HPP

#include "../vector/vector.hpp"

namespace ft
{
    template <typename T, typename Container = ft::vector<T> >
    class stack
    {
        template <typename _Tp, typename _vector>
        friend bool operator==(const stack<_Tp, _vector> &lhs, const stack<_Tp, _vector> &rhs);

        template <typename _Tp, typename _vector>
        friend bool operator<(const ft::stack<_Tp, _vector> &lhs, const ft::stack<_Tp, _vector> &rhs);

    public:
        typedef Container                           container_type;
        typedef typename Container::value_type      value_type;
        typedef typename Container::size_type       size_type;
        typedef typename Container::reference       reference;
        typedef typename Container::const_reference const_reference;

    protected:
        Container c;

    public:
        explicit stack(const Container &cont = Container()) : c(cont) {}
        
        stack(const stack &other) : c(other.c) {}

        stack &operator=(const stack &other)
        {
            c = other.c;
            return *this;
        }
        
        ~stack() {}

        reference top() { return c.back(); }

        const_reference top() const { return c.back(); }

        bool empty() const { return c.empty(); }

        size_type size() const { return c.size(); }

        void push(const value_type &value) { c.push_back(value); }

        void pop() { c.pop_back(); }

        size_t capacity() { return c.capacity(); }
    };

    template< typename _Tp, typename _vector >
	bool operator==( const ft::stack<_Tp,_vector>& lhs, const ft::stack<_Tp,_vector>& rhs )
	{ return lhs.c == rhs.c;}

	template< typename _Tp, typename _vector >
	bool operator!=( const ft::stack<_Tp,_vector>& lhs, const ft::stack<_Tp,_vector>& rhs )
	{ return !(lhs == rhs);}

	template< typename _Tp, typename _vector >
	bool operator<( const ft::stack<_Tp,_vector>& lhs, const ft::stack<_Tp,_vector>& rhs )
	{ return lhs.c < rhs.c;}

	template< typename _Tp, typename _vector >
	bool operator<=( const ft::stack<_Tp,_vector>& lhs, const ft::stack<_Tp,_vector>& rhs )
	{ return !(rhs < lhs);}

	template< typename _Tp, typename _vector >
	bool operator>( const ft::stack<_Tp,_vector>& lhs, const ft::stack<_Tp,_vector>& rhs )
	{ return rhs < lhs;}

	template< typename _Tp, typename _vector >
	bool operator>=( const ft::stack<_Tp,_vector>& lhs, const ft::stack<_Tp,_vector>& rhs )
	{ return !(lhs < rhs);}
};
    
#endif