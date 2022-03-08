

#ifndef MAP_HPP
# define MAP_HPP

# include <functional> 
# include "../Pair.hpp"
# include <limits>
# include "../Iterator.hpp"
# include "../IteratorTraits.hpp"
# include "../ReverseIteratorVector.hpp"
# include <string>

# include <iostream>

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

				typedef		Compare									key_compare;

				class value_compare;
				value_compare	value_comp() const {
					return value_compare(key_compare());
				}

			protected:
					struct Node {

						Node		*parent;
						Node		*predecessor;
						Node		*successor;
						pointer		content;
						short int	balance_factor;

						Node() :
							parent(NULL), predecessor(NULL), successor(NULL), content(NULL), balance_factor(0) { }
						Node(const Node &source) :
							parent(NULL), predecessor(NULL), successor(NULL),
							content(NULL), balance_factor(0) { *this = source; }
						Node(const_reference value) :
							parent(NULL), predecessor(NULL), successor(NULL), content(NULL), balance_factor(0) {
								content = new value_type(value);
							}
						Node(const_reference value, Node *parent) :
							parent(parent), predecessor(NULL), successor(NULL), content(NULL), balance_factor(0) {
								content = new value_type(value);
							}
						Node	operator=(const Node &source) {
							parent = source.parent;
							predecessor = source.parent;
							successor = source.parent;
							pointer new_content = new value_type(*source.content);
							if (content)
								delete content;
							content = new_content;
							balance_factor = source.balance_factor;
							return *this;
						}
						~Node() {
							parent = NULL;
							predecessor = NULL;
							successor = NULL;
							balance_factor = 0;
							delete content;
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
					};

				typedef		Node		node_type;
				typedef		Node *		node_pointer;
				typedef		Node &		node_reference;

				node_pointer	_find_begin() {
					node_pointer rtn = _root;
					while (rtn->predecessor)
						rtn = rtn->predecessor;
					return rtn;
				}
				node_pointer	_find_last() {
					node_pointer rtn = _root;
					while (rtn->successor)
						rtn = rtn->successor;
					return rtn;
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////
				///////////////////////////Class Iterator/////////////////////////////////////////////////////////////
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
							typedef		Node			node_type;
							typedef		Node		*	node_pointer;
							typedef		Node		&	node_reference;
							typedef		const Node	&	const_node_reference;

							node_pointer	_position;
							node_pointer	_root;
							bool			_is_end;

							node_pointer	_find_min(node_pointer pos) {
								while (pos->predecessor)
									pos = pos->predecessor;
								return pos;
							}
							node_pointer	_find_max(node_pointer pos) {
								while (pos->successor)
									pos = pos->successor;
								return pos;
							}


						public:
							IteratorMap()
								: _position(NULL), _root(NULL), _is_end(false) { }
							IteratorMap(node_pointer source, node_pointer root)
								: _position(source), _root(root), _is_end(false) { }

							IteratorMap(node_pointer source, node_pointer root, bool)
								: _position(source), _root(root), _is_end(false) {
									if (source == NULL)
										_is_end = true;
								}
							IteratorMap(const IteratorMap &source)
								: _position(source._position), _root(source._root), _is_end(source._is_end) { }
							~IteratorMap() { }

							//////////////////////////////////Operators////////////////////////////////////////////

							IteratorMap							operator= (const IteratorMap &source) {
								this->_position = source._position;
								this->_root = source._root;
								this->_is_end = source._is_end;
								return *this;
							}
							IteratorMap<const value_type>		operator() () { return (const_iterator(*this)); }

							reference			operator* () { return *_position->content; }
							pointer				operator-> () { return _position->content; }

							//////////////////////////////////Accessors////////////////////////////////////////////

							node_pointer		base() const { return _position; }

							//////////////////////////////////Increment/Decrement//////////////////////////////////

							IteratorMap			&operator++ () {
								if (_position == NULL) {
									if (!_is_end)
										_position = _find_min(_root);
								}
								else if (_position->successor) {
									_position = _find_min(_position->successor);
								}
								else {
									node_pointer tmp = _position;
									while (tmp->parent && *tmp <= *_position) {
										tmp = tmp->parent;
									}
									if (*tmp > *_position)
										_position = tmp;
									else {
										_position = NULL;
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
								if (_position == NULL) {
									if (_is_end)
										_position = _find_max(_root);
									_is_end = false;
								}
								else if (_position->predecessor) {
									_position = _find_max(_position->predecessor);
								}
								else {
									node_pointer	tmp = _position;
									while (tmp->parent && *tmp >= *_position) {
										tmp = tmp->parent;
									}
									if (*tmp < *_position)
										_position = tmp;
									else {
										_position = NULL;
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
					};

				/////////////////////////////////Comparison Operators///////////////////////////////////////

				template<class Type>
					friend bool		operator== (const IteratorMap<Type> &lhs, const IteratorMap<Type> &rhs) {
						return (lhs.base() == rhs.base());
					}
				template<class Type1, class Type2, class TNode>
					friend bool		operator== (const IteratorMap<Type1> &lhs, const IteratorMap<Type2> &rhs) {
						return (lhs.base() == rhs.base());
					}


				template<class Type>
					friend bool		operator!= (const IteratorMap<Type> &lhs, const IteratorMap<Type> &rhs) {
						return (lhs.base() != rhs.base());
					}
				template<class Type1, class Type2>
					friend bool		operator!= (const IteratorMap<Type1> &lhs, const IteratorMap<Type2> &rhs) {
						return (lhs.base() != rhs.base());
					}
				//////////////////////////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////


			public:
				typedef		typename Alloc::template rebind<node_type>::other	allocator_type;

				typedef		IteratorMap<value_type>				iterator;
				typedef		IteratorMap<const value_type>		const_iterator;
				typedef		ReverseIterator<iterator>			reverse_iterator;
				typedef		ReverseIterator<const_iterator>		const_reverse_iterator;


			private:
				allocator_type	_alloc;
				value_compare	_comp;
				node_pointer	_root;
				size_type		_size;

			public:
				/////////////////////////////////Constructors/////////////////////////////////////////////////////////
				map() :
					_alloc(allocator_type()), _comp(key_compare()), _root(NULL), _size(0)  { }
				explicit map(const Compare& comp, const allocator_type& alloc = allocator_type()) :
					_alloc(alloc), _comp(comp), _root(NULL), _size(0) { }
				map(const map &source) { *this = source; }
				// template< class InputIt >
					// map(InputIt first, InputIt last,
							// const Compare& comp = Compare(),
							// const Alloc& alloc = Alloc()) {
					// }

				/////////////////////////////////Destructor///////////////////////////////////////////////////////////
				~map() { }

				/////////////////////////////////Operators////////////////////////////////////////////////////////////
				map		operator= (const map &source) {
					_alloc = source._alloc;
					_comp = source._comp;
					// _root = source._root;
					// _begin = source._begin;   // NEED DEEP COPY WITH iterator
					// _last = source._last;
					// _end = source._end;
					_size = source._size;
				}

				/////////////////////////////////Capacity/////////////////////////////////////////////////////////////
				allocator_type			get_allocator() { return _alloc; }
				bool					empty() const { return !_root; }
				size_type				size() const { return _size; }
				size_type				max_size() const { return std::numeric_limits<size_type>::max(); }

				/////////////////////////////////Modifiers////////////////////////////////////////////////////////////

				/////////////////////////////////Accessors////////////////////////////////////////////////////////////
				
				/////////////////////////////////Iterators////////////////////////////////////////////////////////////
				iterator				begin() { return iterator(_find_begin(), _root); }
				const_iterator			begin() const { return const_iterator(_find_begin(), _root); }

				reverse_iterator		rbegin() { return reverse_iterator(iterator(_find_last(), _root)); }
				const_reverse_iterator	rbegin() const { return const_reverse_iterator(const_iterator(_find_last(), _root)); }

				iterator				end() { return iterator(NULL, _root, int()); }
				const_iterator 			end() const { return const_iterator(NULL, _root, int()); }

				reverse_iterator		rend() { return reverse_iterator(iterator(NULL, _root)); }
				const_reverse_iterator	rend() const { return const_reverse_iterator(const_iterator(NULL, _root)); }

				node_pointer			_create_node(const_reference value, node_pointer parent) {
					return new node_type(value, parent);
				}

				////// TEST //////
				void					_create_tree_test(std::string str, std::string str2, std::string str3) {
					_root = _create_node(value_type(2, str2), NULL);
					_root->predecessor = _create_node(value_type(1, str), _root);
					_root->successor = _create_node(value_type(3, str3), _root);
				}
				void					_create_double_tree_successor_test(std::string str, std::string str2, std::string str3) {
					_root = _create_node(value_type(2, str2), NULL);
					_root->predecessor = _create_node(value_type(1, str), _root);
					_root->successor = _create_node(value_type(4, str3), _root);

					node_pointer	new_tree = _root->successor;
					new_tree->predecessor = _create_node(value_type(3, str), new_tree);
					new_tree->successor = _create_node(value_type(6, str3), new_tree);
					new_tree->successor->successor = _create_node(value_type(7, str3), new_tree->successor);
					new_tree->successor->predecessor = _create_node(value_type(5, str), new_tree->successor);
				}

				void					_create_double_tree_predecessor_test(std::string str, std::string str2, std::string str3) {
					_root = _create_node(value_type(3, str2), NULL);
					_root->predecessor = _create_node(value_type(0, str), _root);
					_root->successor = _create_node(value_type(4, str3), _root);

					node_pointer	new_tree = _root->predecessor; // 0
					new_tree->predecessor = _create_node(value_type(-2, str), new_tree);
					new_tree->successor = _create_node(value_type(1, str2), new_tree);
					new_tree->successor->successor = _create_node(value_type(2, str2), new_tree->successor);
					new_tree->predecessor->predecessor = _create_node(value_type(-3, str3), new_tree->predecessor);
					new_tree->predecessor->successor = _create_node(value_type(-1, str3), new_tree->predecessor);
				}

		};

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

				value_compare	operator= (const value_compare &source) {
					_comp_instance = source._comp_instance;
					return *this;
				}
				return_value	operator() (first_argument_type value1, second_argument_type value2) const {
					return _comp_instance(value1.first, value2.first);
				}

		};



}


#endif
