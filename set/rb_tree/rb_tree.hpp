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
            create_node(&this->_end, _Val(), _allocator);
            if (other._root)
            {
                this->_root = copy(this->_root, other._root, _end, _allocator);
                this->_end->parent = _root->maximum(_root);
                this->_count = other._count;
                _end->left = _root;
            }
            _end->color = BLACK;
        }

        void clear()
        {
            _m_erase(_end);
            _end = 0;
            _root = 0;
            _count = 0;
        }

        rb_tree& operator=(const rb_tree& other) // CHANGED
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


            // if (other._root != NULL)
            // {
            //     _m_erase(this->_end);
            //     _root = NULL;
            //     _end = NULL;
            //     _count = 0;
            //     _end = _allocator.allocate(1);
            //     _allocator.construct(_end, _Val());
            //     _root = _copy(_root, other._root, _end);
            //     _end->parent = maximum(_root);
            //     _count = other._count;
            //     _end->left = _root;
            // }
            // return *this;
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

        void insert(_Base_ptr pos, const _Val& value)
        {
            if (!_root || _root == _end)
                insert(value);
            else if (value_compare()(_root->data, pos->data) && value_compare()(value, _root->data))
                insert(value);
            else if (value_compare()(pos->data, _root->data) && value_compare()(_root->data, value))
                insert(value);
            else
                insert_with_pos(pos, value);
        }

        _Base_ptr insert(const _Val& _value)
        {
            if (!_end)
                create_node(&_end, _Val(), _allocator);
                
            if (search(_value))
                return _root;
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
                _Base_ptr _tmp = GetRoot();
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

        _Base_ptr insert_with_pos(_Base_ptr pos, const _Val& _value)
        {
            if (search(_value))
                return _root;
            if (_root == NULL)
            {
                _root = _allocator.allocate(1);
                _allocator.construct(_root, _value);
                // _root->parent = NULL;
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
                else if (n == _tmp->data)
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

        void deleteByVal(_Val n)
        {
            if (_root == NULL)
                return ;
            
            _Base_ptr v = search(n);

            if (v->data != n)
                return ;

            remove(v);
            _end->left = GetRoot();
            _end->parent = maximum(_root);
            if (_root)
                _root->parent = _end;
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
            // std::swap(u, v);
            if (v->parent && is_on_left(v))
            {
                v->parent->left = u;
                u->parent = v->parent;
                if (v->right)
                {
                    u->right = v->right;
                    v->right->parent = u;
                }
            }
            else
            {
                v->parent->right = u;
                u->parent = v->parent;
                if (v->left)
                {
                    u->left = v->left;
                    v->right->parent = u;
                }
            }
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
                    _root = NULL;
                else
                {
                    if (uvBlack)
                        fix_double_black(root);
                    else
                    {
                        if (get_sibling(root) != NULL)
                            get_sibling(root)->color = RED;
                    }
                    if (is_on_left(root))
                        parent->left = NULL;
                    else
                        parent->right = NULL;
                }
                _allocator.destroy(root);
                _allocator.deallocate(root, 1);
                this->_count -= 1;
                return ;
            }

            if  (root->left == NULL || root->right == NULL)
            {
                if (root == _root)
                {
                    _root = u;
                    _root->left = _root->right = NULL;
                    _allocator.destroy(root);
                    _allocator.deallocate(root, 1);
                    this->_count -= 1;
                }
                else
                {
                    if (is_on_left(root))
                        parent->left = u;
                    else
                        parent->right = u;
                    _allocator.destroy(root);
                    _allocator.deallocate(root, 1);
                    this->_count -= 1;
                    u->parent = parent;
                    if (uvBlack)
                        fix_double_black(u);
                    else
                        u->color = BLACK;
                }
                return ;
            }

            // v has 2 children, swap values with successor and recurse
            _Val _value = u->data;
            _Base_ptr _parent = root->parent;
            _Base_ptr _left = root->left;
            _Base_ptr _right = root->right;
            _allocator.destroy(root);
            _allocator.construct(root, _value);
            root->color = u->color;
            root->parent = _parent;
            root->left = _left;
            root->right = _right;
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
                                // CHANGEED
                                if (sibling->right)
                                    sibling->right->color = parent->color;
                                // right_rotate(sibling);
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