#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include <iostream>

template<typename _Tp, _Tp __v>
struct integral_constant
{
    static _Tp                  value = __v;
    typedef _Tp                           value_type;
    typedef integral_constant<_Tp, __v>   type;
    operator value_type() { return value; }
};

typedef integral_constant<bool, true>     __true_type;
typedef integral_constant<bool, false>    __false_type;
 
template<typename _Tp, _Tp __v>
_Tp integral_constant<_Tp, __v>::value;

namespace ft
{
	template <typename _Tp, _Tp __v> struct integral_constant
	{
		static _Tp							value = __v;
		typedef _Tp							value_type;
		typedef integral_constant<_Tp, __v>	type;
		operator value_type() const {return value;}
	};

	typedef integral_constant<bool, true>								__true_type;
	typedef integral_constant<bool, false>    							__false_type;
	template <class T>	struct	is_integral								{ static const bool value = false; };
	template <> 		struct	is_integral<bool> 						{ static const bool value = true; };
	template <> 		struct	is_integral<char>						{ static const bool value = true; };
	template <> 		struct	is_integral<char16_t>					{ static const bool value = true; };
	template <> 		struct	is_integral<char32_t>					{ static const bool value = true; };
	template <> 		struct	is_integral<wchar_t>					{ static const bool value = true; };
	template <> 		struct	is_integral<signed char>				{ static const bool value = true; };
	template <> 		struct	is_integral<short int>					{ static const bool value = true; };
	template <> 		struct	is_integral<int>						{ static const bool value = true; };
	template <> 		struct	is_integral<long int>					{ static const bool value = true; };
	template <> 		struct	is_integral<long long int>				{ static const bool value = true; };
	template <> 		struct	is_integral<unsigned char>				{ static const bool value = true; };
	template <> 		struct	is_integral<unsigned short int>			{ static const bool value = true; };
	template <> 		struct	is_integral<unsigned int>				{ static const bool value = true; };
	template <> 		struct	is_integral<unsigned long int>			{ static const bool value = true; };
	template <> 		struct	is_integral<unsigned long long int>		{ static const bool value = true; };
};

#endif