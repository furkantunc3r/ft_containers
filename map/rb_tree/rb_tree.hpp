#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "rb_tree_utils.hpp"

enum {BLACK, RED};

namespace ft
{
    template<typename _Val, typename _Compare, typename _Allocator = std::allocator<_Val>>
    class rb_tree
    {
    public:
        typedef typename _Allocator::template rebind<Node<_Val>>::other allocator_type;
        typedef _Val                                                    value_type;
        typedef typename allocator_type::pointer                        pointer;
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

        _Base_ptr       _root;
        size_type       _count;
        _Compare        _key_compare;
        allocator_type  _allocator;

    
        rb_tree() : _root() { }

        _Base_ptr GetRoot() { return _root; }

        void left_rotate(_Base_ptr n)
        {
            _Base_ptr _gp = n->parent->parent;
            _Base_ptr _p = n->parent;

            if (n->left != NULL)
            {
                n->left->parent = _p;
                _p->right = n->left;
            }
            if (_gp == NULL)
            {
                _root = n;
                n->left = _p;
            }
            else if (_p == _gp->left)
                _gp->left = n;
            else
                _gp->right = n;
            _p->parent = n;
            _root->parent = NULL;
        }

        void right_rotate(_Base_ptr n)
        {
            _Base_ptr _gp;
            _Base_ptr _p = n->parent;
            if (n->parent->parent != NULL)
                _gp = n->parent->parent;
            else
                _gp = NULL;
            if (n->right != NULL)
            {
                n->right->parent = _p;
                _p->left = n->right;
            }
            if (_gp == NULL)
            {
                _root = n;
                n->right = _p;
            }
            else if (_p == _gp->right)
                _gp->right = n;
            else
                _gp->left = n;
            _p->parent = n;
            _root->parent = NULL;
        }

        void insert(const _Val& _value)
        {
            if (_root == NULL)
            {
                _root = new ft::Node<_Val>();
                _root->data = _value;
                _root->parent = NULL;
                _root->color = BLACK;
            }
            else
            {
                _Base_ptr _tmp = GetRoot();
                _Base_ptr _new = new ft::Node<_Val>();

                while (_tmp != NULL)
                {
                    if (_tmp->data < _value)
                    {
                        if (_tmp->right == NULL)
                        {
                            _new->parent = _tmp;
                            _tmp->right = _new;
                            _new->data = _value;
                            _new->left = NULL;
                            _new->right = NULL;
                            _new->color = RED;
                            break ;
                        }
                        else
                            _tmp = _tmp->right;
                    }
                    else
                    {
                        if (_tmp->left == NULL)
                        {
                            _new->parent = _tmp;
                            _tmp->left = _new;
                            _new->data = _value;
                            _new->left = NULL;
                            _new->right = NULL;
                            _new->color = RED;
                            break ;
                        }
                        else
                            _tmp = _tmp->left;
                    }
                }
                rb_insert_fix(_new);
            }
        }

        void rb_insert_fix(_Base_ptr n)
        {
            _Base_ptr _gp = n->parent->parent;
            while (n->parent != NULL && n->parent->color == RED)
            {
                if (_gp != NULL && n->parent == _gp->left)
                {
                    if (_gp->right != NULL && _gp->right->color == RED)
                    {
                        _gp->right->color = BLACK;
                        _gp->left->color = BLACK;
                        _gp->color = RED;
                        n = _gp;
                    }
                    else if (n->parent != NULL && n == n->parent->right)
                    {
                        n = n->parent;
                        left_rotate(n);
                    }
                    else
                    {
                        n->parent->color = BLACK;
                        _gp->color = RED;
                        right_rotate(_gp);
                    }
                }
                else if (_gp != NULL && n->parent == _gp->right)
                {
                    if (_gp->left->color == RED)
                    {
                        _gp->right->color = BLACK;
                        _gp->left->color = BLACK;
                        _gp->color = RED;
                        n = _gp;
                    }
                    else if (n == n->parent->left)
                    {
                        n = n->parent;
                        right_rotate(n);
                        n->parent->color = BLACK;
                        _gp->color = RED;
                        left_rotate(_gp);
                    }
                }
            }
            _root->color = BLACK;
        }
    };
};

#endif