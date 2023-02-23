#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "rb_tree_utils.hpp"
#include "tree_iterator.hpp"
#include "../../reverse_iterator.hpp"

enum {BLACK, RED};

namespace ft
{
    template<typename _Val, typename _Compare, typename _Allocator = std::allocator<_Val> >
    class rb_tree
    {
    public:
        typedef typename _Allocator::template rebind<Node<_Val> >::other    allocator_type;
        typedef _Val                                                        value_type;
        typedef typename allocator_type::pointer                            pointer;
        typedef typename allocator_type::const_pointer                      const_pointer;
        typedef typename allocator_type::reference                          reference;
        typedef typename allocator_type::const_reference                    const_reference;
        typedef size_t                                                      size_type;
        typedef ptrdiff_t                                                   difference_type;
        typedef ft::tree_iterator<value_type>                               iterator;
        typedef ft::const_tree_iterator<value_type>                         const_iterator;
        typedef ft::reverse_iterator<iterator>                              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                        const_reverse_iterator;
        
        typedef ft::Node<_Val>*                                             _Base_ptr;

        _Base_ptr       _root;
        _Base_ptr       _end;
        size_type       _count;
        _Compare        _key_compare;
        allocator_type  _allocator;
    
        rb_tree() : _root(), _end(), _count(0), _key_compare(), _allocator()
        {
            create_node(&this->_end, _Val(), _allocator);
            _end->color = BLACK;
        }

        rb_tree(const _Compare& _comp, const allocator_type& _a = allocator_type()) : _root(), _end(), _count(0), _key_compare(_comp), _allocator(_a)
        {
            create_node(&this->_end, _Val(), _allocator);
            _end->color = BLACK;
        }

        rb_tree(const rb_tree& other) : _count(0), _key_compare(other._key_compare), _allocator(other._allocator)
        {
            if (other._root)
            {
                create_node(&this->_end, _Val(), _allocator);
                this->_root = copy(this->_root, other._root, _end, _allocator);
                this->_end->parent = _root->maximum(_root);
                this->_count = other._count;
                _end->left = _root;
                _end->color = BLACK;
            }
        }

        void clear()
        {
            _m_erase(_end);
            _end = 0;
            _root = 0;
            _count = 0;
        }

        rb_tree& operator=(const rb_tree& other)
        {
            if (this != &other)
            {
                clear();
                _key_compare = other._key_compare;
                _allocator = other._allocator;
                if (other._root != 0)
                {
                    create_node(&_end, _Val(), _allocator);
                    _root = _copy(_root, other._root, _end);
                    _count = other._count;
                    _end->left = _root;
                    _end->parent = _root->maximum(_root);
                }
            }
            return *this;
        }

        ~rb_tree()
        {
            _m_erase(_end);
        }

        _Base_ptr _copy(_Base_ptr tree, _Base_ptr first, _Base_ptr parent)
        {
            if (!first)
                return _root;
            create_node(&tree, first->data, _allocator);
            tree->parent = parent;
            tree->left = _copy(tree->left, first->left, tree);
            tree->right = _copy(tree->right, first->right, tree);
            return tree;
        }

        void _m_erase(_Base_ptr _x)
        {
            if (_x)
			{
				_m_erase(_x->left);
				_m_erase(_x->right);
				this->_allocator.destroy(_x);
				this->_allocator.deallocate(_x, 1);
			}
        }

        _Base_ptr GetRoot() { return _root; }

        _Compare value_compare() const { return _key_compare; }

        iterator lower_bound(const value_type& _value)
        {
            _Base_ptr ret = _end;
            _Base_ptr _node = _root;
            
            while (_node)
            {
                if (!value_compare()(_node->data, _value))
                {
                    ret = _node;
                    _node = _node->left;
                }
                else
                    _node = _node->right;
            }
            return iterator(ret);
        }

        const_iterator lower_bound(const value_type& _value) const
        {
            _Base_ptr ret = _end;
            _Base_ptr _node = _root;
            
            while (_node)
            {
                if (!value_compare()(_node->data, _value))
                {
                    ret = _node;
                    _node = _node->left;
                }
                else
                    _node = _node->right;
            }
            return const_iterator(ret);
        }

        iterator upper_bound(const value_type& _value)
        {
            _Base_ptr ret = _end;
            _Base_ptr _node = _root;
            
            while (_node)
            {
                if (value_compare()(_value, _node->data))
                {
                    ret = _node;
                    _node = _node->left;
                }
                else
                    _node = _node->right;
            }
            return iterator(ret);
        }

        const_iterator upper_bound(const value_type& _value) const
        {
            _Base_ptr ret = _end;
            _Base_ptr _node = _root;
            
            while (_node)
            {
                if (value_compare()(_value, _node->data))
                {
                    ret = _node;
                    _node = _node->left;
                }
                else
                    _node = _node->right;
            }
            return const_iterator(ret);
        }
        
        void left_rotate(_Base_ptr x)
        {
            _Base_ptr y = x->right;
            x->right = y->left;

            if (y->left != NULL)
                y->left->parent = x;
            y->parent = x->parent;
            if (x->parent == _end)
                this->_root = y;
            else if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
            y->left = x;
            x->parent = y;
        }

        void right_rotate(_Base_ptr x)
        {
            _Base_ptr y = x->left;
            x->left = y->right;

            if (y->right != NULL)
                y->right->parent = x;
            y->parent = x->parent;
            if (x->parent == _end)
                this->_root = y;
            else if (x == x->parent->right)
                x->parent->right = y;
            else
                x->parent->left = y;
            y->right = x;
            x->parent = y;
        }

        _Base_ptr insert(const _Val& _value)
        {
            int exists = 0;
            _Base_ptr _new = NULL;
            _Base_ptr insert_pos = search(&exists, _value);

            if (!exists)
            {
                _new = insert_at(insert_pos, _value);
                return _new;
            }
            return insert_pos;
        }

        void insert(_Base_ptr pos, const _Val& value)
        {
            int exists = 0;
            if (!_root || _root == _end)
                insert(value);
            else if (value_compare()(_root->data, pos->data) && value_compare()(value, _root->data))
                insert(value);
            else if (value_compare()(pos->data, _root->data) && value_compare()(_root->data, value))
                insert(value);
            else
            {
                search(&exists, value);
                if (!exists)
                    insert_at(pos, value);
            }
        }

        _Base_ptr insert_at(_Base_ptr pos, const value_type& _value)
        {
            if (!_end)
                create_node(&_end, _Val(), _allocator);

            if (_root == NULL)
            {
                _root = _allocator.allocate(1);
                _allocator.construct(_root, _value);
                _root->color = BLACK;
                this->_count += 1;
                _end->left = GetRoot();
                _root->parent = _end;
                _end->parent = maximum(_root);
            }
            else
            {
                _Base_ptr _tmp = pos;
                _Base_ptr _new;
                _new = _allocator.allocate(1);

                while (_tmp != NULL)
                {
                    if (value_compare()(_tmp->data, _value))
                    {
                        if (_tmp->right == NULL)
                        {
                            _allocator.construct(_new, _value);
                            _new->parent = _tmp;
                            _tmp->right = _new;
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
                            _allocator.construct(_new, _value);
                            _new->parent = _tmp;
                            _tmp->left = _new;
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
                this->_count += 1;
                _end->left = GetRoot();
                _root->parent = _end;
                _end->parent = maximum(_root);
                return _new;
            }
            return _root;
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
                        right_rotate(_gp);
                    }
                }
                else if (_gp != NULL && n->parent == _gp->right)
                {
                    if (_gp->left != NULL && _gp->left->color == RED)
                    {
                        _gp->left->color = BLACK;
                        _gp->right->color = BLACK;
                        _gp->color = RED;
                        n = _gp;
                    }
                    else
                    {
                        if (n == n->parent->left)
                        {
                            n = n->parent;
                            right_rotate(n);
                        }
                        n->parent->color = BLACK;
                        _gp->color = RED;
                        left_rotate(_gp);
                    }
                }
                if (n == _root)
                    break ;
            }
            _root->color = BLACK;
        }

        _Base_ptr minimum(_Base_ptr n)
        {
            if (!n || !n->left)
                return n;
            return minimum(n->left);
        }

        _Base_ptr maximum(_Base_ptr n)
        {
            if (!n || !n->right)
                return n;
            return maximum(n->right);
        }

        _Base_ptr search(_Val n) const
        {
            _Base_ptr _tmp = _root;

            while (_tmp != NULL)
            {
                if (value_compare()(n, _tmp->data))
                {
                    if (_tmp->left == NULL)
                        return NULL;
                    else
                        _tmp = _tmp->left;
                }
                else if (n.first == _tmp->data.first)
                    break ;
                else
                {
                    if (_tmp->right == NULL)
                        return NULL;
                    else
                        _tmp = _tmp->right;
                }
            }
            return _tmp;
        }

        _Base_ptr search(int *exists, _Val n) const
        {
            _Base_ptr _tmp = _root;

            while (_tmp != NULL)
            {
                if (value_compare()(n, _tmp->data))
                {
                    if (_tmp->left == NULL)
                        break ;
                    else
                        _tmp = _tmp->left;
                }
                else if (n.first == _tmp->data.first)
                {
                    *exists = 1;
                    break ;
                }
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

        void deleteByVal(iterator n)
        {
            if (_root == NULL)
                return ;
            
            remove(n._M_node);    
            this->_allocator.destroy(n._M_node);
            this->_allocator.deallocate(n._M_node, 1);
            this->_count--;
            _end->left = GetRoot();
            _end->parent = maximum(_root);
            if (_root)
                _root->parent = _end;
        }
        
        void tree_transplant_node(_Base_ptr pos, _Base_ptr node)
        {
            node->color = pos->color;
            node->parent = pos->parent;
            
            if (pos == pos->parent->left)
                node->parent->left = node;
            else
                node->parent->right = node;
            node->left = pos->left;
            node->left->parent = node;
            node->right = pos->right;
            if (node->right)
                node->right->parent = node;
        }

        void remove(_Base_ptr target)
        {
            _Base_ptr y = target;
            // Find node to replace target if target has 2 child (in order successor)
            if (y->left != NULL && y->right != NULL)
                y = minimum(target->right);

            // x is NULL or y's only child
            _Base_ptr x;
            if (y->left != NULL)
                x = y->left;
            else
                x = y->right;

            // keep track of x's parent
            _Base_ptr x_parent = y->parent;

            // Replace y with x
            if (x != NULL)
                x->parent = y->parent;
            if (y == y->parent->left)
            {
                y->parent->left = x;
                if (_root == y)
                    _root = x;
            }
            else
            {
                // If y is target's right child, update x_parent because target will be replaced by y later
                if (target->right == y)
                    x_parent = y;
                y->parent->right = x;
            }

            // Keep track of removed color before possibly transplanting y into target's place
            bool removed_black = false;
            if (y->color == BLACK)
                removed_black = true;
            
            // If y is target's in order successor, transplant y into target's place
            if (y != target)
            {
                tree_transplant_node(target, y);
                if (target == _root)
                    _root = y;
            }

            // Balance tree only if a black node was removed
            if (removed_black)
            {
                // Tree is empty, nothing to do(root double black case)
                if (_root == NULL)
                    return;

                // x is red, color it black
                if (x != NULL)
                {
                    x->color = BLACK;
                    return ;
                }
                tree_delete_fix(x_parent);
            }
        }

        void tree_delete_fix(_Base_ptr x_parent)
        {
            // Double black nodes always start as a null pointer
            _Base_ptr x = NULL;

            while (_root != x && (x == NULL || x->color == BLACK))
            {
                if (x == x_parent->left)
                {
                    _Base_ptr w = x_parent->right;

                    if (w->color == RED) // case 1
                    {
                        x_parent->color = RED;
                        w->color = BLACK;
                        left_rotate(x_parent);
                        w = x_parent->right;
                    }

                    if ((w->left == NULL || w->left->color == BLACK) && (w->left == NULL || w->right->color == BLACK)) // case 2 && case 3
                    {
                        w->color = RED;
                        x = x_parent;
                        x_parent = x->parent;
                    }
                    else
                    {
                        if ((w->right == NULL || w->right->color == BLACK)) // case 4
                        {
                            w->color = RED;
                            right_rotate(w);
                            w = x_parent->right;
                            w->color = BLACK;
                        }

                        // case 5
                        w->color = x_parent->color;
                        x_parent->color = BLACK;
                        w->right->color = BLACK;
                        left_rotate(x_parent);
                        x = _root;
                        break ;
                    }
                }
                else
                {
                    _Base_ptr w = x_parent->left;

                    if (w->color == RED) // case 1
                    {
                        x_parent->color = RED;
                        w->color = BLACK;
                        right_rotate(x_parent);
                        w = x_parent->left;
                    }

                    if ((w->right == NULL || w->right->color == BLACK) && (w->left == NULL || w->left->color == BLACK)) // case 2 && case 3
                    {
                        w->color = RED;
                        x = x_parent;
                        x_parent = x->parent;
                    }
                    else
                    {
                        if ((w->left == NULL || w->left->color == BLACK)) // case 4
                        {
                            w->color = RED;
                            left_rotate(w);
                            w = x_parent->left;
                            w->color = BLACK;
                        }

                        // case 5
                        w->color = x_parent->color;
                        x_parent->color = BLACK;
                        w->left->color = BLACK;
                        right_rotate(x_parent);
                        x = _root;
                        break ;
                    }
                }
            }
            if (x) // case 0 + 2 when parent was red
                x->color = BLACK;
        }

        iterator begin() { return iterator(this->_root->minimum(_end)); }
        const_iterator begin() const { return const_iterator(this->_root->minimum(_end)); }
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
        
        iterator end() { return iterator(_end); }
        const_iterator end() const { return const_iterator(_end); }
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

        bool empty() const { return this->_count == 0; }
    };

    template<typename _Val, typename _Compare, typename _Alloc>
    bool operator==(const ft::rb_tree<_Val, _Compare, _Alloc>& _x,
        const ft::rb_tree<_Val, _Compare, _Alloc>& _y)
        {
            return _x._count == _y._count
                && ft::equal(_x.begin(), _x.end(), _y.begin());
        }

    template<typename _Val, typename _Compare, typename _Alloc>
    bool operator<(const ft::rb_tree<_Val, _Compare, _Alloc>& _x,
        const ft::rb_tree<_Val, _Compare, _Alloc>& _y)
        {
            return ft::lexicographical_compare(_x.begin(), _x.end(),
                                        _y.begin(), _y.end());
        }
    
    template<typename _Val, typename _Compare, typename _Alloc>
    bool operator!=(const ft::rb_tree<_Val, _Compare, _Alloc>& _x,
        const ft::rb_tree<_Val, _Compare, _Alloc>& _y)
        {
            return !(_x == _y);
        }
    
    template<typename _Val, typename _Compare, typename _Alloc>
    bool operator>(const ft::rb_tree<_Val, _Compare, _Alloc>& _x,
        const ft::rb_tree<_Val, _Compare, _Alloc>& _y)
        {
            return _y < _x;
        }
    
    template<typename _Val, typename _Compare, typename _Alloc>
    bool operator<=(const ft::rb_tree<_Val, _Compare, _Alloc>& _x,
        const ft::rb_tree<_Val, _Compare, _Alloc>& _y)
        {
            return !(_y < _x);
        }
    
    template<typename _Val, typename _Compare, typename _Alloc>
    bool operator>=(const ft::rb_tree<_Val, _Compare, _Alloc>& _x,
        const ft::rb_tree<_Val, _Compare, _Alloc>& _y)
        {
            return !(_x < _y);
        }
};

#endif