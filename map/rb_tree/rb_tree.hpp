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

        _Base_ptr search(_Val n)
        {
            _Base_ptr _tmp = _root;

            while (_tmp != NULL)
            {
                if (n < _tmp->data)
                {
                    if (_tmp->left == NULL)
                        break ;
                    else
                        _tmp = _tmp->left;
                }
                else if (n == _tmp->data)
                    break ;
                else
                {
                    if (_tmp->right == NULL)
                        break ;
                    else
                        _tmp = _tmp->right;
                }
            }
            return _tmp;
        }

        void deleteByVal(_Val n)
        {
            if (_root == NULL)
                return ;
            
            _Base_ptr v = search(n);

            if (v->data != n)
                return ;

            remove(v);
        }

        _Base_ptr phantom_node(_Base_ptr x)
        {
            if (x->left != NULL && x->right != NULL)
                return maximum(x->left);
            if (x->left == NULL && x->right == NULL)
                return NULL;

            if (x->left != NULL)
                return x->left;
            else
                return x->right;
        }

        void swap_values(_Base_ptr u, _Base_ptr v)
        {
            _Val _tmp;

            _tmp = u->data;
            u->data = v->data;
            v->data = _tmp;
        }

        bool is_on_left(_Base_ptr x)
        {
            if (x == x->parent->left)
                return 1;
            return 0;
        }

        _Base_ptr get_sibling(_Base_ptr x)
        {
            if (x->parent == NULL)
                return NULL;
            if (is_on_left(x))
                return x->parent->right;
            return x->parent->left;  
        }

        void remove(_Base_ptr root)
        {
            _Base_ptr u = phantom_node(root);
            _Base_ptr parent = root->parent;

            bool uvBlack = ((u == NULL || u->color == BLACK) && (root->color == BLACK));

            if (u == NULL)
            {
                if (root == _root)
                    root = NULL;
                else
                {
                    if (uvBlack)
                        fix_double_black(root);
                    else
                        if (get_sibling(root) != NULL)
                            get_sibling(root)->color = RED;
                    if (is_on_left(root))
                        parent->left = NULL;
                    else
                        parent->right = NULL;
                }
                delete root;
                return ;
            }

            if  (root->left == NULL || root->right == NULL)
            {
                if (root == _root)
                {
                    root->data = u->data;
                    root->left = root->right = NULL;
                    delete u;
                }
                else
                {
                    if (is_on_left(root))
                        parent->left = u;
                    else
                        parent->right = u;
                    delete root;
                    u->parent = parent;
                    if (uvBlack)
                        fix_double_black(u);
                    else
                        u->color = BLACK;
                }
                return ;
            }

            // v has 2 children, swap values with successor and recurse
            swap_values(u, root);
            remove(u);
        }

        bool has_red_child(_Base_ptr x)
        {
            if ((x->left != NULL && x->left->color == RED) || (x->right != NULL && x->right->color == RED))
                return 1;
            return 0;
        }

        void fix_double_black(_Base_ptr x)
        {
            if (x == _root)
                return ;

            _Base_ptr sibling = get_sibling(x);
            _Base_ptr parent = x->parent;

            if (sibling == NULL)
                fix_double_black(parent);
            else
            {
                if (sibling->color == RED)
                {
                    parent->color = RED;
                    sibling->color = BLACK;
                if (is_on_left(sibling))
                    right_rotate(parent);
                else
                    left_rotate(parent);
                fix_double_black(x);
                }
                else
                {
                    if (has_red_child(sibling))
                    {
                        if (sibling->left != NULL && sibling->left->color == RED)
                        {
                            if (is_on_left(sibling))
                            {
                                sibling->left->color = sibling->color;
                                sibling->color = parent->color;
                                right_rotate(parent);
                            }
                            else
                            {
                                sibling->left->color = parent->color;
                                right_rotate(sibling);
                                left_rotate(parent);
                            }
                        }
                        else
                        {
                            if (is_on_left(sibling))
                            {
                                sibling->right->color = parent->color;
                                left_rotate(sibling);
                                right_rotate(parent);
                            }
                            else
                            {
                                sibling->right->color = sibling->color;
                                sibling->color = parent->color;
                                left_rotate(parent);
                            }
                        }
                        parent->color = BLACK;
                    }
                    else
                    {
                        sibling->color = RED;
                        if (parent->color == BLACK)
                            fix_double_black(parent);
                        else
                            parent->color = BLACK;
                    }
                }
            }
        }
    };
};

#endif