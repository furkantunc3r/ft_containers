#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "rb_tree_utils.hpp"

namespace ft
{
    template<typename _Val, typename _Compare, typename _Allocator = std::allocator<_Val>>
    class rb_tree
    {
    public:
        typedef typename _Allocator::template rebind<Node<_Val>>::other allocator_type;
        typedef _Val                                                    value_type;
        typedef typename allocator_type::pointer                        pointer:
        typedef typename allocator_type::const_pointer                  const_pointer;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef size_t                                                  size_type;
        typedef ptrdiff_t                                               difference_type;
        //iterator
        //iterator
        //iterator
        //iterator
        typedef ft::Node<_Val>* _Base_ptr;

        _Base_ptr       _tree;
        _Base_ptr       _end;
        size_type       _count;
        _Compare        _key_compare;
        allocator_type  _allocator;

    private:
        void _M_erase(_Base_ptr _x)
        {
            if (_x)
            {
                _M_erase(_x->left);
                _M_erase(_x->right);
                this->_allocator.destroy(_x);
                this->_allocator.deallocate(_x, 1);
            }
        }
    public:
        rb_tree() : _tree(), _end(), _count(0), _key_compare(), _allocator()
        {
            create_node(&this->_end, _Val(), _allocator();)
        }

        
    };
};

#endif