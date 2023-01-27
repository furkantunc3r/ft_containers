#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft
{
    template<bool, typename _Tp = void>
    struct enable_if { };
    
    template<typename _Tp>
    struct enable_if<true, _Tp> { typedef _Tp type; };
}

#endif