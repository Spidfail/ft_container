
#ifndef MAP_HPP
# define MAP_HPP

# include <algorithm>
# include <climits>
# include <cstddef>
# include <functional> 
# include "Pair.hpp"
# include <limits>
# include "Iterator.hpp"
# include "IteratorTraits.hpp"
# include "ReverseIterator.hpp"
# include <string>
# include <queue>
# include <math.h>
# include "EnableIf.hpp"
# include "IsIntegral.hpp"

# include <iostream>

# define PREDECESSOR	0 
# define SUCCESSOR		1 
# define NONE			-1 

namespace ft {

	template <class Key,
			 class T,
			 class Compare = std::less<Key>,
			 class Alloc = std::allocator< ft::pair<const Key, T> > >
		class map {

			public:
				typedef		Key										key_type;
				typedef		T										mapped_type;
				typedef		ptrdiff_t								difference_type;
				typedef		size_t									size_type;

				typedef 	ft::pair<const key_type, mapped_type> 	value_type;
				typedef		value_type &							reference;
				typedef		const value_type &						const_reference;
				typedef		value_type *							pointer;
				typedef		const value_type *						const_pointer;
				typedef		Alloc									allocator_type;

				typedef		Compare									key_compare;

				class value_compare;

				value_compare	value_comp() const { return value_compare(key_compare()); }
				key_compare		key_comp() const { return key_compare(); }

			protected:
				//////////////////////////////////////////////////////////////////////////////////////////////////////
				///////////////////////////Declaration Node///////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////
				template< typename ValueNode, typename AllocNode = std::allocator< ValueNode > >
					struct Node {

						typedef		AllocNode		allocator_type;	// Overight map type
						typedef		ValueNode		value_type;		// Overight map type
						typedef		value_type	*	pointer;		// Overight map type

						allocator_type	alloc;
						Node			*parent;
						Node			*predecessor;
						Node			*successor;
						pointer			content;
						ssize_t			balance_factor;
						ssize_t			height;

						Node() :
							alloc(allocator_type()), parent(NULL), predecessor(NULL), successor(NULL),
							content(NULL), balance_factor(0), height(0) { }
						Node(const Node &source) :
							alloc(allocator_type()), parent(NULL), predecessor(NULL), successor(NULL),
							content(NULL), balance_factor(0), height(0) { *this = source; }
						Node(const_reference value) :
							alloc(allocator_type()), parent(NULL), predecessor(NULL), successor(NULL),
							content(NULL), balance_factor(0), height(0) {
								content = allocate_content(value_type(value));
							}
						Node(const_reference value, Node *parent) :
							alloc(allocator_type()), parent(parent), predecessor(NULL), successor(NULL),
							content(NULL), balance_factor(0), height(0) {
								content = allocate_content(value_type(value));
							}
						Node	&operator=(const Node &source) {
							pointer new_content = NULL;
							if (source.content)
								new_content = allocate_content(*source.content);
							if (content) {
								alloc.destroy(content);
								alloc.deallocate(content, 1);
							}
							content = new_content;
							parent = source.parent;
							predecessor = source.predecessor;
							successor = source.successor;
							balance_factor = source.balance_factor;
							height = source.height;
							return *this;
						}
						~Node() {
							if (content) {
								alloc.destroy(content);
								alloc.deallocate(content, 1);
							}
							content = NULL;
							parent = NULL;
							predecessor = NULL;
							successor = NULL;
							balance_factor = 0;
							height = 0;
						}

						const key_type		&get_key() { return content->first; }
						const mapped_type	&get_mapped() { return content->second; }
						const pointer		get_value() { return content; }
						Node				*get_successor() { return successor; }
						Node				*get_predecessor() { return predecessor; }
						Node				*get_parent() { return parent; }
						ssize_t				get_balance_factor() { return balance_factor; }
						ssize_t				get_height() { return height; }

						size_type			count_children() {
							if (successor && predecessor)
								return 2;
							else if (successor || predecessor)
								return 1;
							return 0;
						}
						bool				is_parent() { return parent; }

						void				set_content(const_reference val) {
							alloc.destroy(content);
							alloc.deallocate(content, 1);
							content = allocate_content(val);
						}

						void				assign_pointers(const Node *target) {
							if (target == this)
								return ;
							this->successor = target->successor;
							this->predecessor = target->predecessor;
							this->parent = target->parent;
						}

						void				assign_height(const Node *target) {
							this->height = target->height;
							this->balance_factor = target->balance_factor;
						}

						// Reset all pointers of this node, set at NULL.
						// Do not destroy or deallocate memory.
						void				reset_relations() {
							this->successor = NULL;
							this->predecessor = NULL;
							this->parent = NULL;
						}

						// Used to ensure relation with all pointer of *this.
						// Segfault protected.
						// No leak protection : he could erase pointer's own assignations.
						void				ensure_relations() {
							if (this->successor)
								this->successor->parent = this;
							if (this->predecessor)
								this->predecessor->parent = this;
						}

						friend	bool	operator<(const Node &lhs, const Node &rhs) {
							return value_compare()(*lhs.content, *rhs.content);
						}

						friend	bool	operator>(const Node &lhs, const Node &rhs) {
							return (!(lhs == rhs) && !(lhs < rhs));
						}

						friend	bool	operator<=(const Node &lhs, const Node &rhs) {
							return (lhs < rhs || (lhs == rhs));
						}

						friend	bool	operator>=(const Node &lhs, const Node &rhs) {
							return (!(lhs < rhs));
						}

						friend	bool	operator==(const Node &lhs, const Node &rhs) {
							return (lhs.content->first == rhs.content->first);
						}

						friend	bool	operator!=(const Node &lhs, const Node &rhs) {
							return (!(lhs == rhs));
						}

						private:
							pointer			allocate_content(const_reference	instance) {
									pointer		new_content = alloc.allocate(1);
									alloc.construct(new_content, instance);
									return new_content;
							}

					};

				///////////////////////////////////Node Utils/////////////////////////////////////////////////////////
				//
				//These aren't Node member functions and typedef.
				//They meant to be used by map methods and functions.
				typedef		Node<value_type, Alloc>		node_type;
				typedef		node_type				*	node_pointer;
				typedef		node_type				&	node_reference;
				typedef		const node_type			&	const_node_reference;

				node_pointer	find_begin() const {
					if (!_root)
						return NULL;
					node_pointer rtn = _root;
					while (rtn->predecessor)
						rtn = rtn->predecessor;
					return rtn;
				}
				node_pointer	find_last() const {
					if (!_root)
						return NULL;
					node_pointer rtn = _root;
					while (rtn->successor)
						rtn = rtn->successor;
					return rtn;
				}
				//find the leftmost node of node pos.
				static node_pointer		find_min(node_pointer pos) {
					while (pos->predecessor)
						pos = pos->predecessor;
					return pos;
				}
				//find the rightmost node of node pos.
				static node_pointer		find_max(node_pointer pos) {
					while (pos->successor)
						pos = pos->successor;
					return pos;
				}

				size_type	height_recurse(node_pointer subtree, int i) {
					if (!subtree)
						return i;
					++i;
					if (!subtree->successor && !subtree->predecessor)
						return i;
					size_type	pred_value = height_recurse(subtree->predecessor, i);
					size_type	succ_value = height_recurse(subtree->successor, i);
					return pred_value > succ_value ? pred_value : succ_value;
				}
				size_type	height(node_pointer subtree) {
					size_type	pred_value = height_recurse(subtree->predecessor, 0);
					size_type	succ_value = height_recurse(subtree->successor, 0);
					return pred_value > succ_value ? pred_value : succ_value;
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////


				//////////////////////////////////////////////////////////////////////////////////////////////////////
				///////////////////////////Declaration Iterator///////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////

				template <typename Value>
					class IteratorMap {

						typedef 	typename 	ft::iterator_traits<typename ft::iterator<std::bidirectional_iterator_tag, Value> >		iterator_traits_type;

						public :
							typedef		typename	iterator_traits_type::difference_type		difference_type;
							typedef		typename	iterator_traits_type::value_type			value_type;
							typedef		typename	iterator_traits_type::pointer				pointer;
							typedef		typename	iterator_traits_type::reference				reference;
							typedef		typename	iterator_traits_type::iterator_category		iterator_category;

						private:
							node_pointer	_position;
							bool			_is_out;
							bool			_is_end;

							node_pointer	find_begin(node_pointer pos) {
								node_pointer	cp(pos);
								while (cp->get_parent()) {
									cp = cp->parent;
								}
								return (find_min(cp));
							}
							node_pointer	find_last(node_pointer pos) {
								node_pointer	cp(pos);
								while (cp->get_parent()) {
									cp = cp->parent;
								}
								return (find_max(cp));
							}

							ssize_t	get_balance_factor() {
								return _position->get_balance_factor();
							}

							ssize_t	get_weight_successor() {
								return _position->get_weight_successor();
							}
							ssize_t	get_weight_predecessor() {
								return _position->get_weight_predecessor();
							}

						public:
							IteratorMap()
								: _position(NULL), _is_out(false), _is_end(false) { }

							IteratorMap(const node_pointer &source)
								: _position(source), _is_out(false), _is_end(false) { }

							IteratorMap(const node_pointer &source, bool is_end)
								: _position(source), _is_out(true), _is_end(is_end) {
								}

							IteratorMap(const IteratorMap &source)
								: _position(source._position), _is_out(source._is_out), _is_end(source._is_end) { }
							~IteratorMap() { }

							//////////////////////////////////Operators////////////////////////////////////////////

							IteratorMap			&operator= (const IteratorMap &source) {
								this->_position = source._position;
								this->_is_out = source._is_out;
								this->_is_end = source._is_end;
								return *this;
							}
							operator	IteratorMap<const value_type>() const {
								if (_is_end && _is_out)
									return (IteratorMap<const value_type>(_position, true));
								else if (_is_end)
									return (IteratorMap<const value_type>(_position, false));
								return (IteratorMap<const value_type>(_position));
							}

							reference			operator* () const {
								if (_is_out || _position == NULL)
									return *_position->successor->content;
								return *_position->content;
							}
							pointer				operator-> () const {
								if (_is_out || _position == NULL)
									return NULL;
								return _position->content;
							}

							//////////////////////////////////Accessors/////////////////////////////////////
							node_pointer		base() const { return _position; }

							//////////////////////////////////Increment/Decrement///////////////////////////
							// Used extern methods :
							//  find_min()
							//  find_max()
							//
							IteratorMap			&operator++ () {
								if (_position == NULL)
									return *this;
								if (_is_out) {
									if (!_is_end) {
										_position = find_begin(_position);
										_is_end = false;
										_is_out = false;
										return *this;
									}
								}
								if (_position->successor) {
									_is_out = false;
									_position = find_min(_position->successor);
								}
								else {
									node_pointer tmp = _position;
									while (tmp->parent && !(*tmp > *_position)) {
										tmp = tmp->parent;
									}
									if (*tmp > *_position) {
										_is_out = false;
										_position = tmp;
									}
									else {
										_is_out = true;
										_is_end = true;
									}
								}
								return *this;
							}
							IteratorMap			operator++ (int) {
								IteratorMap		cp(*this);
								++(*this);
								return cp;
							}

							IteratorMap			&operator-- () {
								if (_position == NULL)
									return *this;
								if (_is_out) {
									if (_is_end) {
										_position = find_last(_position);
										_is_end = false;
										_is_out = false;
										return *this;
									}
								}
								if (_position->predecessor) {
									_is_out = false;
									_position = find_max(_position->predecessor);
								}
								else {
									node_pointer	tmp = _position;
									while (tmp->parent && !(*tmp < *_position)) {
										tmp = tmp->parent;
									}
									if (*tmp < *_position) {
										_is_out = false;
										_position = tmp;
									}
									else {
										_is_out = true;
										_is_end = false;
									}
								}
								return *this;
							}
							IteratorMap			operator-- (int) {
								IteratorMap		cp(*this);
								--(*this);
								return cp;
							}

							/////////////////////////////////Comparison Operators Iterators/////////////////////////////
							template<class Type>
								friend bool		operator== (const IteratorMap<Type> &lhs, const IteratorMap<Type> &rhs);
							template<class Type1, class Type2>
								friend bool		operator== (const IteratorMap<Type1> &lhs, const IteratorMap<Type2> &rhs);

							template<class Type>
								friend bool		operator!= (const IteratorMap<Type> &lhs, const IteratorMap<Type> &rhs);
							template<class Type1, class Type2>
								friend bool		operator!= (const IteratorMap<Type1> &lhs, const IteratorMap<Type2> &rhs);

					};

				/////////////////////////////////Comparison Operators Iterators/////////////////////////////
				template<class Type>
					friend bool		operator== (const IteratorMap<Type> &lhs, const IteratorMap<Type> &rhs) {
						return  lhs._is_end == rhs._is_end && lhs._is_out == rhs._is_out && lhs.base() == rhs.base();
					}
				template<class Type1, class Type2>
					friend bool		operator== (const IteratorMap<Type1> &lhs, const IteratorMap<Type2> &rhs) {
						return  lhs._is_end == rhs._is_end && lhs._is_out == rhs._is_out && lhs.base() == rhs.base();
					}

				template<class Type>
					friend bool		operator!= (const IteratorMap<Type> &lhs, const IteratorMap<Type> &rhs) {
						return !(lhs == rhs);
					}
				template<class Type1, class Type2>
					friend bool		operator!= (const IteratorMap<Type1> &lhs, const IteratorMap<Type2> &rhs) {
						return !(lhs == rhs);
					}


				////////////////////////////////////////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////////////////////////////////////////

			public:
				typedef		typename Alloc::template rebind<node_type>::other	allocator_node;

				typedef		IteratorMap<value_type>				iterator;
				typedef		IteratorMap<const value_type>		const_iterator;
				typedef		ReverseIterator<iterator>			reverse_iterator;
				typedef		ReverseIterator<const_iterator>		const_reverse_iterator;


			private:
				////////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////Private Variables///////////////////////////////////////
				allocator_type	_alloc;
				allocator_node	_node_alloc;
				value_compare	_comp;
				node_pointer	_root;
				size_type		_size;
				size_type		_max_size;

				////////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////Insert Utils///////////////////////////////////////////

				// Private typedef
				typedef		ft::pair<node_pointer,bool>		search_return;
				typedef		ft::pair<iterator,bool>			insert_return;
				// .first : predecessor,  .second : successor
				typedef		ft::pair<ssize_t, ssize_t>		subtree_height;

				node_pointer	rotation_right(node_pointer subtree) {
					node_pointer	b = subtree->successor;

					subtree->successor = b->predecessor;
					if (subtree->successor)
						subtree->successor->parent = subtree;
					b->parent = subtree->parent;
					subtree->parent = b;
					b->predecessor = subtree;
					update_values(subtree);
					update_values(b);
					return b;							// return the node to set the parent child
				}

				node_pointer	rotation_left(node_pointer subtree) {
					node_pointer	b = subtree->predecessor;

					subtree->predecessor = b->successor;
					if (subtree->predecessor)
						subtree->predecessor->parent = subtree;
					b->parent = subtree->parent;
					subtree->parent = b;
					b->successor = subtree;
					update_values(subtree);
					update_values(b);
					return b;							// return the node to set the parent child
				}

				node_pointer	rotation_right_left(node_pointer subtree) {
					node_pointer	b = subtree->successor;
					node_pointer	c = b->predecessor;

					subtree->successor = c->predecessor;
					if (subtree->successor)
						subtree->successor->parent = subtree;
					b->predecessor = c->successor;
					if (b->predecessor)
						b->predecessor->parent = b;

					c->parent = subtree->parent;
					c->predecessor = subtree;
					c->successor = b;
					subtree->parent = c;
					b->parent = c;
					update_values(subtree);
					update_values(b);
					update_values(c);
					return c;							// return the node to set the parent child
				}

				node_pointer	rotation_left_right(node_pointer subtree) {
					node_pointer	b = subtree->predecessor;
					node_pointer	c = b->successor;

					subtree->predecessor = c->successor;
					if (subtree->predecessor)
						subtree->predecessor->parent = subtree;
					b->successor = c->predecessor;
					if (b->successor)
						b->successor->parent = b;

					c->parent = subtree->parent;
					c->successor = subtree;
					c->predecessor = b;
					subtree->parent = c;
					b->parent = c;
					update_values(subtree);
					update_values(b);
					update_values(c);
					return c;							// return the node to set the parent child
				}

				node_pointer	balance(node_pointer subtree) {
					if (subtree->balance_factor < -1) {
						if (subtree->successor->balance_factor <= 0)
							return rotation_right(subtree);
						else
							return rotation_right_left(subtree);
					}
					else if (subtree->balance_factor > 1) {
						if (subtree->predecessor->balance_factor >= 0)
							return rotation_left(subtree);
						else
							return rotation_left_right(subtree);
					}
					return subtree;
				}

				// Update height and balance factor of current 'subtree'.
				// They are based on children's height.
				void			update_values(node_pointer subtree) {
					subtree_height		sub_height = get_subtree_height(subtree);
					subtree->height = std::max(sub_height.first, sub_height.second) + 1;
					subtree->balance_factor = sub_height.first - sub_height.second;
				}

				node_pointer	insert_recurse(const_reference val, insert_return &wrapper, node_pointer subtree, node_pointer parent) {
					if (subtree == NULL) {
						wrapper.first = iterator(create_node(val, parent));
						wrapper.second = true;
						return wrapper.first.base();
					}
					// Recurse if there is a leaf
					if (val.first == subtree->content->first) {
						wrapper.first = iterator(subtree);
						wrapper.second = false;
						return subtree;
					}
					else if (_comp(val, *subtree->content))
						subtree->predecessor = insert_recurse(val, wrapper, subtree->predecessor, subtree);
					else 
						subtree->successor = insert_recurse(val, wrapper, subtree->successor, subtree);
					// Update the balance factor of it's children
					update_values(subtree);
					// Rotate if balance_factor > 1 || balance_factor < -1
					return balance(subtree);
				}
				////////////////////////////////////////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////////////////////////////////////////

			private:
				/////////////////////////////////Erase Utils////////////////////////////////////////////////

				// Return NULL if there is no replacement.
				node_pointer			disconnect_and_substitute_erase(node_pointer subtree, node_pointer replacement) {
					if (replacement) {
						replacement->parent = subtree->parent;
						update_values(replacement);
					}
					subtree->reset_relations();
					return replacement;
				}

				node_pointer			erase_no_child(const node_pointer &subtree) {
					// if parent == NULL, subtree is root by definition.
					if (subtree->parent == NULL) {
						erase_node(_root);
						_root = NULL;
						return NULL;
					}
					erase_node(subtree);
					return NULL;
				}

				node_pointer			erase_one_child(const node_pointer &subtree) {
					node_pointer		replacement;
					// if pred is the only child of subtree.
					// else, succ is the only child of subtree.
					if (subtree->predecessor)
						replacement = subtree->predecessor;
					else
						replacement = subtree->successor;
					replacement->parent = subtree->parent;
					erase_node(subtree);
					// update_values to check balance_factor later.
					update_values(replacement);
					return balance(replacement);
				}

				// Call recursive function to find subtree replacement.
				// Replace subtree at his position. Erase the node.
				// Return the replacement.
				node_pointer			erase_two_children(node_pointer subtree) {
					node_pointer	replacement;
					subtree_height	heights = get_subtree_height(subtree);
					// Recursive on subtree, return a node_pointer to keep travelled subtrees balanced
					if (heights.first <= heights.second) {
						// Case if there is no child to recurse on
						if (subtree->successor->predecessor == NULL) {
							replacement = subtree->successor;
							replacement->parent = subtree->parent;
							replacement->predecessor = subtree->predecessor;
							replacement->predecessor->parent = replacement;
							erase_node(subtree);
							update_values(replacement);
							return replacement;
						}
						subtree->successor = find_replacement_erase(replacement, subtree->successor, PREDECESSOR);
					}
					else {
						// Case if there is no child to recurse on
						if (subtree->predecessor->successor == NULL) {
							replacement = subtree->predecessor;
							replacement->parent = subtree->parent;
							replacement->successor = subtree->successor;
							replacement->successor->parent = replacement;
							erase_node(subtree);
							update_values(replacement);
							return replacement;
						}
						subtree->predecessor = find_replacement_erase(replacement, subtree->predecessor, SUCCESSOR);
					}
					// Set and place replacement node and erase subree
					replacement->assign_pointers(subtree);
					replacement->ensure_relations();
					erase_node(subtree);
					// values and balance factor are checked in main function, not here.
					return replacement;
				}

				// Find the node, disconnect the node, replace it if it must.
				// Recursively update values and rotate if it must.
				// Return NULL if there is one child to recurse on.
				node_pointer			find_replacement_erase(node_pointer &replacement, node_pointer subtree, bool direction) {
					if (direction == PREDECESSOR) {
						if (subtree->predecessor == NULL) {
							replacement = subtree;
							if (replacement->successor && replacement->successor->get_key() == 13)
								std::cerr << " BEFOR SUBTITUTION : " << subtree->successor->get_key() << std::endl;
							return disconnect_and_substitute_erase(replacement, replacement->successor);
						}
						subtree->predecessor = find_replacement_erase(replacement, subtree->predecessor, direction);
						if (subtree->predecessor && subtree->predecessor->get_key() == 13)
							std::cerr << " AFTER SUBTITUTION : " << subtree->predecessor->get_key() << std::endl;
					}
					else {
						if (subtree->successor == NULL) {
							replacement = subtree;
							return disconnect_and_substitute_erase(replacement, replacement->predecessor);
						}
						subtree->successor = find_replacement_erase(replacement, subtree->successor, direction);
					}
					update_values(subtree);
					return balance(subtree);
				}

				// Recursive. Search the target, redirect to functions depending on the number of children.
				// Update values and balance the tree.
				node_pointer			find_node_erase(node_pointer target, node_pointer subtree) {
					// if the target doesn't exists
					if (subtree == NULL)
						return NULL;
					// if the target is reached
					else if (target == subtree) {
						if (subtree->count_children() == 2)
							subtree = erase_two_children(subtree);
						else if (subtree->count_children() == 1)
							subtree = erase_one_child(subtree);
						else
							subtree = erase_no_child(subtree);
					}
					// otherwise, recurse on children
					else if (*target > *subtree)
						subtree->successor = find_node_erase(target, subtree->successor);
					else
						subtree->predecessor = find_node_erase(target, subtree->predecessor);
					if (subtree) {
						update_values(subtree);
						return balance(subtree);
					}
					return subtree;
				}

				////////////////////////////////////////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////////////////////////////////////////

			private:
				////////////////////////////////////////////////////////////////////////////////////////////
				////////////////////////////Map Utils///////////////////////////////////////////////////////

#ifdef DEBUG
			public:
				// Check if the tree is balanced.
				bool _is_valid() { return _is_valid_sub(_root).first; }
#endif /////////////////////////////////////  DEBUG

				ft::pair<bool, int> _is_valid_sub(node_pointer node) {
					if (node == NULL) return ft::make_pair(true, 0);
					ft::pair<bool, int> left = _is_valid_sub(node->predecessor);
					ft::pair<bool, int> right = _is_valid_sub(node->successor);
					int height = std::max(left.second, right.second) + 1;
					return ft::make_pair(left.first && right.first && std::abs(left.second - right.second) < 2, height);
				}

				// Depends on #define at the top :
				// 		PREDECESSOR = 0;
				// 		SUCCESSOR = 1;
				// 		NONE = -1;
				int					is_side(node_pointer subtree) {
					if (!subtree->parent)
						return NONE;
					if (*subtree->parent->successor == *subtree)
						return SUCCESSOR;
					return PREDECESSOR;
				}

				size_type			calculate_max_size() {
					return std::numeric_limits<size_type>::max() / sizeof(Node<key_type,mapped_type>);
				}


				/////////////////////////////////Node methode PRIVATE///////////////////////////////////////
				node_pointer		create_node(const_reference value) {
					node_pointer	new_node = _node_alloc.allocate(1);
					_node_alloc.construct(new_node, node_type(value));
					return new_node;
				}

				node_pointer		create_node(const_reference value, node_pointer parent) {
					node_pointer	new_node = _node_alloc.allocate(1);
					_node_alloc.construct(new_node, node_type(value, parent));
					return new_node;
				}

				// See also : erase_tree(node_pointer subtree);
				void				erase_node(const node_pointer &node) {
					_node_alloc.destroy(node);
					_node_alloc.deallocate(node, 1);
					--_size;
				}

				// Recursive function, always return NULL
				node_pointer		erase_tree(const node_pointer &subtree) {
					if (subtree == NULL)
						return subtree;
					subtree->predecessor = erase_tree(subtree->predecessor);
					subtree->successor = erase_tree(subtree->successor);
					erase_node(subtree);
					return NULL;
				}

				// This function duplicate a tree but doesn't destroy/deallocate his content.
				node_pointer		duplicate_tree(node_pointer subtree) {
					if (subtree == NULL)
						return NULL;
					node_pointer	replacement = _node_alloc.allocate(1);
					_node_alloc.construct(replacement, *subtree->content);
					replacement->predecessor = duplicate_tree(subtree->predecessor);
					replacement->successor = duplicate_tree(subtree->successor);
					if (replacement->predecessor)
						replacement->predecessor->parent = replacement;
					if (replacement->successor)
						replacement->successor->parent = replacement;
					return replacement;
				}

				// See 'update_values' for it's use in recursive form.
				subtree_height	get_subtree_height(const node_pointer &subtree) {
					ssize_t		pred_height = -1;
					ssize_t		succ_height = -1;

					if (subtree->predecessor)
						pred_height = subtree->predecessor->height;
					if (subtree->successor)
						succ_height = subtree->successor->height;
					return ft::make_pair(pred_height, succ_height);
				}


				/////////////////////////////////Search Tools/////////////////////////////////////////////////////

				// See also : search_operation(const_reference val, node_pointer subtree)
				// 		> Search a content (value_type) instead of a node_pointer (Node *).
				search_return		search_operation(const node_pointer	&elem, const node_pointer &subtree) const {
					if (*subtree > *elem) {
						if (subtree->predecessor)
							return search_operation(elem, subtree->predecessor);
						else
							return search_return(subtree, false);
					}
					else if (*subtree < *elem) {
						if (subtree->successor)
							return search_operation(elem, subtree->successor);
						else
							return search_return(subtree, false);
					}
					return search_return(subtree, true);
				}

				// See also : search_operation(node_pointer elem, node_pointer subtree)
				// 		> Search a node_pointer (Node *) instead of a content (value_type).
				search_return		search_operation(const_reference val, const node_pointer &subtree) const {
					if (val == *subtree->get_value())
						return search_return(subtree, true);
					else if (_comp(val, *subtree->get_value())) {
						if (subtree->predecessor)
							return search_operation(val, subtree->predecessor);
						else
							return search_return(subtree, false);
					}
					else {
						if (subtree->successor)
							return search_operation(val, subtree->successor);
						else
							return search_return(subtree, false);
					}
				}

			public:
				////////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////Map Declaration////////////////////////////////////////////

				/////////////////////////////////Constructors///////////////////////////////////////////////
				//
				// allocator_type	_alloc;
				// allocator_node	_node_alloc;
				// value_compare	_comp;
				// node_pointer		_root;
				// size_type		_size;
				// size_type		_max_size;
				//
				map() :
					_alloc(allocator_type()), _node_alloc(allocator_node()), _comp(key_compare()),
					_root(NULL), _size(0), _max_size(calculate_max_size()) { }

				explicit map(const Compare& comp, const allocator_type& alloc = allocator_type()) :
					_alloc(alloc), _node_alloc(allocator_node()), _comp(comp),
					_root(NULL), _size(0), _max_size(calculate_max_size()) { }

				map(const map &source)
					: _root(NULL), _size(0) { *this = source; }

				template<class InputIt>
					map(InputIt first, InputIt last,
							const Compare& comp = Compare(),
							const Alloc& alloc = Alloc()) : 
						_alloc(alloc), _node_alloc(allocator_node()), _comp(comp), _root(NULL),
						_size(0), _max_size(calculate_max_size()) {
							insert(first, last);
					}

				/////////////////////////////////Destructor/////////////////////////////////////////////////
				~map() { clear(); }

				/////////////////////////////////Operators//////////////////////////////////////////////////
				// Deep copy
				map		&operator= (const map &source) {
					node_pointer	new_root = duplicate_tree(source._root);
					if (_root)
						_root = erase_tree(_root);
					_root = new_root;
					_alloc = source._alloc;
					_node_alloc = source._node_alloc;
					_comp = source._comp;
					_size = source._size;
					return *this;
				}

				/////////////////////////////////Accessors//////////////////////////////////////////////////
				mapped_type				&operator[] (const key_type &k) {
					return	(* ( (this->insert( ft::make_pair(k,mapped_type())) ).first ) ).second;
				}

				/////////////////////////////////Iterators////////////////////////////////////////////////////////////
				//// Constructore available :
				// IteratorMap(node_pointer source);					// For begin() iterators
				// IteratorMap(node_pointer source, bool is_end);		// For end()/rend()
				//
				iterator				begin() {
					if (_root)
						return iterator(find_begin());
					return iterator(NULL);
				}
				const_iterator			begin() const { 
					if (_root)
						return const_iterator(find_begin());
					return const_iterator(NULL);
				}

				reverse_iterator		rbegin() {
					if (_root)
						return reverse_iterator(iterator(find_last()));
					return reverse_iterator(iterator(NULL));
				}
				const_reverse_iterator	rbegin() const {
					if (_root)
						return const_reverse_iterator(iterator(find_last()));
					return const_reverse_iterator(iterator(NULL));
				}

				iterator				end() {
					if (_root)
						return iterator(find_last(), true);
					return iterator(NULL, true);
				}
				const_iterator 			end() const {
					if (_root)
						return const_iterator(find_last(), true);
					return const_iterator(NULL, true);
				}

				reverse_iterator		rend() {
					if (_root)
						return reverse_iterator(iterator(find_begin(), false));
					return reverse_iterator(iterator(NULL, false));
				}
				const_reverse_iterator	rend() const {
					if (_root)
						return const_reverse_iterator(iterator(find_begin(), false));
					return const_reverse_iterator(iterator(NULL, false));
				}

				/////////////////////////////////Capacity///////////////////////////////////////////////////
				allocator_type			get_allocator() { return _alloc; }
				bool					empty() const { return !_root; }
				size_type				size() const { return _size; }
				size_type				max_size() const {
					return _max_size; 
				}

				/////////////////////////////////Modifiers//////////////////////////////////////////////////
				void					clear() {
					_root = erase_tree(_root);
					_size = 0;
				}

				ft::pair<iterator,bool>		insert(const value_type& val) {
					if (_root == NULL) {
						_root = create_node(val, NULL);
						++_size;
						return insert_return(iterator(_root), true);
					}
					insert_return	return_value(iterator(), false);
					_root = insert_recurse(val, return_value, _root, NULL);
					if (return_value.second)
						++_size;
					return return_value;
				}

				iterator 				insert(iterator, const value_type& val) {
					return insert(val).first;
				}

				template <class InputIterator>
					void 				insert (InputIterator first, InputIterator last) {
						for (; first != last ; ++first)
							insert(*first);
					}


			public:
				/////////////////////////////////Erase Public///////////////////////////////////////////////
				void 					erase(iterator pos) {
					if (pos.base() == NULL || pos == this->end())
						return ;
					_root = find_node_erase(pos.base(), _root);
				}

				size_type 				erase(const Key& key) {
					iterator	it(find(key));
					if (it != end()) {
						erase(it);
						return 1;
					}
					return 0;
				}

				void 					erase(iterator first, iterator last) {
					iterator	it_end(this->end());
					while (first != it_end && first != last) {
						iterator	it_cpy(first);
						++first;
						erase(it_cpy);
					}
				}

				void					swap(map &other) {
					std::swap(this->_comp, other._comp);
					std::swap(this->_alloc, other._alloc);
					std::swap(this->_node_alloc, other._node_alloc);
					std::swap(this->_root, other._root);
					std::swap(this->_size, other._size);
				}

				/////////////////////////////////Lookup/////////////////////////////////////////////////////
				size_type 		count(const Key& key) const {
					if (search_operation(ft::make_pair(key, mapped_type()), _root).second)
						return 1;
					return 0;
				}

				iterator		find(const Key& key) {
					if (_root) {
						search_return rtn = search_operation(ft::make_pair(key, mapped_type()), _root);
						if (rtn.second)
							return rtn.first;
					}
					return this->end();
				}

				const_iterator	find(const Key& key) const { return find(key); }

				ft::pair<iterator, iterator>				equal_range(const key_type &key) {
					return ft::make_pair(find(key), ++(find(key)));
				}
				ft::pair<const_iterator, const_iterator>	equal_range(const key_type &key) const {
					return ft::make_pair(find(key), ++(find(key)));
				}

				iterator 		lower_bound( const Key& key ) { return find(key); }
				const_iterator	lower_bound( const Key& key ) const { return find(key); }

				iterator 		upper_bound( const Key& key ) { return ++find(key); }
				const_iterator	upper_bound( const Key& key ) const { return ++find(key); }
		};

	////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////Comparison Operators///////////////////////////////////////
	
	template< class Key, class T, class Compare, class Alloc >
		bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs ) {
			if (lhs.empty() && rhs.empty())
				return true;
			if (lhs.size() == rhs.size())
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			return false;
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs ) {
			return !(lhs == rhs);
		}

	template <class Key, class T, class Compare, class Alloc>
		bool operator<  ( const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs ) {
			if ((lhs.empty() && rhs.empty()) || (!lhs.empty() && rhs.empty()))
				return false;
			else if (lhs.empty() && !rhs.empty())
				return true;
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

	template <class Key, class T, class Compare, class Alloc>
		bool operator<=  ( const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs ) {
			return lhs < rhs || lhs == rhs;
		}

	template <class Key, class T, class Compare, class Alloc>
		bool operator>  ( const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs ) {
			return lhs != rhs && !(lhs < rhs);
		}

	template <class Key, class T, class Compare, class Alloc>
		bool operator>=  ( const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs ) {
			return !(lhs < rhs);
		}

	////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////Value compare Declaration//////////////////////////////////

	template <class Key, class T, class Compare, class Alloc>
		class ft::map<Key, T, Compare, Alloc>::value_compare : std::binary_function<value_type, value_type, bool> {

			friend class map;

			private:
				value_compare() { }

			protected:
				Compare		_comp_instance;
				value_compare(Compare source) : _comp_instance(source) { }

			public:
				typedef		bool				return_value;
				typedef		const_reference		first_argument_type;
				typedef		const_reference		second_argument_type;
				value_compare(const value_compare &source) :
					_comp_instance(source._comp_instance) { }
				~value_compare() { }

				value_compare	&operator= (const value_compare &source) {
					_comp_instance = source._comp_instance;
					return *this;
				}
				return_value	operator() (first_argument_type value1, second_argument_type value2) const {
					return _comp_instance(value1.first, value2.first);
				}
		};


}


#endif
