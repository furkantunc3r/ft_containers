#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "rb_tree_utils.hpp"

enum {BLACK, RED};

namespace ft
{
    template<typename _Val, typename _Compare, typename _Allocator = std::allocator<_Val> >
    class rb_tree
    {
    public:
        typedef typename _Allocator::template rebind<Node<_Val> >::other allocator_type;
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
            {
                _p->left = n->right;
                _p->left->left = n;
                _p->left->parent = _p;
                n->parent = _p->left;
                n->right = NULL;
            }
            else
                _gp->right = n;
            _gp = n;
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
                n->right->parent = n;
            }
            else if (_p == _gp->right)
                _gp->right = n;
            else
            {
                n->right = _gp->left;
                _gp->left->left = NULL;
                _gp->left = n;
                n->parent = _gp;
            }
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
            while (n->parent != NULL && n->parent->color == RED)
            {
                _Base_ptr _gp = n->parent->parent;
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
                        right_rotate(n->parent);
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

        _Base_ptr minimum(_Base_ptr n)
        {
            while (n->left != NULL)
                n = n->left;
            return n;
        }

        _Base_ptr maximum(_Base_ptr n)
        {
            while (n->right != NULL)
                n = n->right;
            return n;
        }

        void rb_transplant(_Base_ptr u, _Base_ptr v) // change to operator overload later
        {
            if (u->parent == NULL)
                _root = v;
            else if (u == u->parent->left)
                u->parent->left = v;
            else
                u->parent->right = v;
            if (v != NULL)
                v->parent = u->parent;
        }
        void remove(_Base_ptr n, int key)
        {
            _Base_ptr   z = NULL;
            _Base_ptr   x;
            _Base_ptr   y;

            while (n != NULL)
            {
                if (n->data == key)
                    z = n;
                if (n->data < key)
                {
                    n = n->right;
                }
                else
                    n = n->left;
            }

            if ( z == NULL)
            {
                std::cout << "Key not found" << std::endl;
                return ;
            }

            y = z;
            int y_org_color = y->color;
            if (z->left == NULL)
            {
                x = z->right;
                rb_transplant(z, z->right);
            }
            else if (z->right == NULL)
            {
                x = z->left;
                rb_transplant(z, z->left);
            }
            else
            {
                y = maximum(z->left);
                y_org_color = y->color;
                x = y->right;
                if (x != NULL && (y == z->right || y == z->left))
                    x->parent = y;
                else if (y != NULL && y->right != NULL)
                {
                    rb_transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                rb_transplant(z, y);
                y->right = z->right;
                y->color = z->color;
            }
            delete z;
            if (y_org_color == BLACK)
                rb_remove_fix(x);
        }

        void rb_remove_fix(_Base_ptr n)
        {
            _Base_ptr s;

            while (n != NULL && n != _root && n->color == RED)
            {
                if (n == n->parent->left)
                {
                    s = n->parent->right;
                    if (s->color == BLACK)
                    {
                        s->color = BLACK;
                        n->parent->color = RED;
                        left_rotate(n->parent);
                        s = n->parent->right;
                    }
                    if (s->left->color == BLACK && s->right->color == BLACK)
                    {
                        s->color = 1;
                        n = n->parent;
                    }
                    else
                    {
                        if (s->right->color == BLACK)
                        {
                            s->left->color = BLACK;
                            s->color = RED;
                            right_rotate(s);
                            s = n->parent->right;
                        }
                        s->color = n->parent->color;
                        n->parent->color = BLACK;
                        s->right->color = BLACK;
                        left_rotate(n->parent);
                        n = _root;
                    }
                }
                else
                {
                    s = n->parent->left;
                    if (s->color == RED)
                    {
                        s->color = BLACK;
                        n->parent->color = RED;
                        right_rotate(n->parent);
                        s = n->parent->left;
                    }
                    if ( s->right->color == BLACK && s->right->color == BLACK)
                    {
                        s->color = RED;
                        n = n->parent;
                    }
                    else
                    {
                        if (s->left->color == BLACK)
                        {
                            s->right->color = BLACK;
                            s->color = RED;
                            left_rotate(s);
                            s = n->parent->left;
                        }
                        s->color = n->parent->color;
                        n->parent->color = BLACK;
                        s->parent->color = BLACK;
                        right_rotate(n->parent);
                        n = _root;
                    }
                }
            }
            if (n != NULL)
                n->color = BLACK;
        }
    };
};

#endif