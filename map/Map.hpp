

#ifndef MAP_HPP
# define MAP_HPP

# include <functional> 
# include "../Pair.hpp"
# include <limits>
# include "../Iterator.hpp"
# include "../IteratorTraits.hpp"
# include "../ReverseIteratorVector.hpp"
# include <string>
# include <queue>
# include <math.h>

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
				typedef		Alloc									allocator_type;

				typedef		Compare									key_compare;

				class value_compare;
				value_compare	value_comp() const {
					return value_compare(key_compare());
				}

friend	void	print_tree();
			protected:
					struct Node {

						private:
							pointer			allocate_content(const_reference	instance) {
									pointer		new_content = alloc.allocate(1);
									alloc.construct(new_content, instance);
									return new_content;
							}


						allocator_type	alloc;
						Node			*parent;
						Node			*predecessor;
						Node			*successor;
						pointer			content;
						size_type		weight_pred;
						size_type		weight_succ;

						Node() :
							alloc(allocator_type()), parent(NULL), predecessor(NULL), successor(NULL),
							content(NULL), weight_pred(0), weight_succ(0) { }
						Node(const Node &source) :
							alloc(allocator_type()), parent(NULL), predecessor(NULL), successor(NULL),
							content(NULL), weight_pred(0), weight_succ(0) { *this = source; }
						Node(const_reference value) :
							alloc(allocator_type()), parent(NULL), predecessor(NULL), successor(NULL),
							content(NULL), weight_pred(0), weight_succ(0) {
								content = allocate_content(value_type(value));
							}
						Node(const_reference value, Node *parent) :
							alloc(allocator_type()), parent(parent), predecessor(NULL), successor(NULL),
							content(NULL), weight_pred(0), weight_succ(0) {
								content = allocate_content(value_type(value));
							}
						Node	&operator=(const Node &source) {
							parent = source.parent;
							predecessor = source.predecessor;
							successor = source.successor;
							pointer new_content = allocate_content(value_type(*source.content));
							if (content)
								alloc.deallocate(content, 1);
							content = new_content;
							weight_pred = source.weight_pred;
							weight_succ = source.weight_succ;
							return *this;
						}
						~Node() {
							parent = NULL;
							predecessor = NULL;
							successor = NULL;
							weight_pred = 0;
							weight_succ = 0;
							alloc.deallocate(content, 1);
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
					while (rtn->predecessor){
						rtn = rtn->predecessor;
					}
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

							IteratorMap							&operator= (const IteratorMap &source) {
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
				typedef		typename Alloc::template rebind<node_type>::other	allocator_node;

				typedef		IteratorMap<value_type>				iterator;
				typedef		IteratorMap<const value_type>		const_iterator;
				typedef		ReverseIterator<iterator>			reverse_iterator;
				typedef		ReverseIterator<const_iterator>		const_reverse_iterator;


			private:
				allocator_type	_alloc;
				allocator_node	_node_alloc;
				value_compare	_comp;
				node_pointer	_root;
				size_type		_size;


				void			_add_weight() {

				}

				node_pointer	_insert_recursion(node_pointer	elem, node_pointer	subtree) {
					if (*subtree == *elem)
						return subtree;
					else if (*subtree < *elem) {
						if (subtree->predecessor) {
							node_pointer rtn = _insert_recursion(elem, subtree->predecessor);
							if (rtn)
								return rtn;
							else
								++subtree->weight_pred;
						}
						else {
							subtree->predecessor = elem;
							++subtree->weight_pred;
						}
					}
					else if (*subtree > *elem) {
						if (subtree->successor) {
							node_pointer rtn = _insert_recursion(elem, subtree->successor);
							if (rtn)
								return rtn;
							else
								++subtree->weight_succ;
						}
						else {
							subtree->successor = elem;
							++subtree->weight_succ;
						}
					}
				}

			public:

void	print_tree()
		{
			std::cout<<"dans print tree\n";
			int i = 0;
			int tour = 0;
			// std::cout<<"dans print tree1.25"<<head->getKey()<<"\n";
			int space = pow(2,_root->height() -1 );
			// std::cout<<"dans print tree1.35\n";
			int vide = 0;
			int v = 1;
			int debug = 0;
			std::queue<Node*> n;
			// std::cout<<"dans print tree1.5\n";
			// std::cout<<"dans print tree1.75\n";
			node_pointer temp;
			node_pointer temp_head = _root;
			n.push(temp_head);
			node_pointer temp2;
			for (int x = 0 ; x <space ; x++)
			{
				std::cout<<" ";
			}
			while(!n.empty() )//&& debug < 15)
			{
				// std::cout<<"dans print tree2\n";
				debug++;
				temp = n.front();
				n.pop();
				if (temp->getKey() == '*')
					std::cout<<(char)(temp->getKey());
				else
					std::cout<<(temp->getKey());
				i++;
				if (i != 0 && i == pow(2,tour)/2)
					std::cout<<" ";
				if(i == pow(2,tour))
				{
					if (v == 0)
					{
						std::cout<<"\n";
						return;
					}
					std::cout<<"\n";
					for (int x = 0 ; x <space -pow(2,tour); x++)
					{
						std::cout<<" ";
					}
					tour++;
					i = 0;
					v = 0;
				}
				if (temp->getKey() == '*')
				{
					pair<const char,int> p1('*' , 0);
					temp2 = _node_alloc.allocate(1);
					_node_alloc.construct(temp2, node_type(p1));
					n.push(temp2);
					temp2 = _node_alloc.allocate(1);
					_node_alloc.construct(temp2, node_type(p1));
					n.push(temp2);
					delete temp;
					continue;
				}
				if(temp->getLeft()!= 0)
				{
					// std::cout<<"dans left ";
					n.push(temp->getLeft());
					if (temp->getKey()!='*')
						v++;
				}
				else
				{
					pair<const char,int> p1('*' , 0);
					temp2 = _node_alloc.allocate(1);
					_node_alloc.construct(temp2, node_type(p1));
					n.push(temp2);
				}
				if(temp->getRight()!= 0)
				{
					// std::cout<<"dans right ";
					n.push(temp->getRight());
					if (temp->getKey()!='*')
						v++;
				}
				else
				{
					pair<const char,int> p1('*' , 0);
					temp2 = _node_alloc.allocate(1);
					_node_alloc.construct(temp2, node_type(p1));
					n.push(temp2);
					// n.push(Node<Key,T,Alloc>("*",0));
					vide ++;
				}
				// std::cout<<"v == "<<v<<" ";
			}
			std::cout<<"\n";
		}

				/////////////////////////////////Constructors/////////////////////////////////////////////////////////
				//
				// allocator_type	_alloc;
				// allocator_node	_node_alloc;
				// value_compare	_comp;
				// node_pointer	_root;
				// size_type		_size;
				//
				map() :
					_alloc(allocator_type()), _node_alloc(allocator_node()), _comp(key_compare()), _root(NULL), _size(0) { }

				explicit map(const Compare& comp, const allocator_type& alloc = allocator_type()) :
					_alloc(alloc), _node_alloc(allocator_node()), _comp(comp), _root(NULL), _size(0) { }

				map(const map &source) { *this = source; }
				// template< class InputIt >
					// map(InputIt first, InputIt last,
							// const Compare& comp = Compare(),
							// const Alloc& alloc = Alloc()) {
					// }

				/////////////////////////////////Destructor///////////////////////////////////////////////////////////
				~map() { }

				/////////////////////////////////Node methode PRIVATE/////////////////////////////////////////////////
				node_pointer			_create_node(const_reference value, node_pointer parent) {
					node_pointer	new_node = _node_alloc.allocate(1);
					_node_alloc.construct(new_node, node_type(value, parent));
					return new_node;
				}

				////// TEST ////////////////////////
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
				// pair<iterator,bool>		insert (const value_type& val) {
				// }

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
