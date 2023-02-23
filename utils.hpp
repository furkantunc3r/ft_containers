#ifndef UTILS_HPP
#define UTILS_HPP

#include "normal_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
    template <typename, typename>
    struct __are_same
    {
        enum { __value = 0 };
        typedef __false_type __type;
    };

    template <typename _Tp>
    struct __are_same<_Tp, _Tp>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };

    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        while (first1!=last1)
        {
          if (first2==last2 || *first2<*first1) return false;
          else if (*first1<*first2) return true;
          ++first1; ++first2;
        }
        return (first2!=last2);
    }

    template <class InputIterator1, class InputIterator2>
    bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
    {
      while (first1!=last1) {
        if (!(*first1 == *first2))
          return false;
        ++first1; ++first2;
      }
      return true;
    }
}
#endif