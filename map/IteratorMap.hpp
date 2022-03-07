

#ifndef ITERATORMAP_HPP 
# define ITERATORMAP_HPP

# include "../IteratorTraits.hpp"
# include "../Iterator.hpp"
# include <xlocale/__wctype.h>
# include "Node.hpp"

namespace ft {

	template <typename T, typename TNode>
		class IteratorMap {

			typedef 	typename 	ft::iterator_traits<typename ft::iterator<std::bidirectional_iterator_tag, T> >		iterator_traits_type;

			public :
				typedef		typename	iterator_traits_type::difference_type		difference_type;
				typedef		typename	iterator_traits_type::value_type			value_type;
				typedef		typename	iterator_traits_type::pointer				pointer;
				typedef		typename	iterator_traits_type::reference				reference;
				typedef		typename	iterator_traits_type::iterator_category		iterator_category;

			private:
				typedef		IteratorMap<const value_type, TNode>		const_iterator;

				typedef		TNode			node_type;
				typedef		TNode	*		node_pointer;
				typedef		TNode	&		node_reference;
				typedef		const TNode	&	const_node_reference;

				node_pointer	_position;
				node_pointer	_root;
				bool			_is_end;

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
				IteratorMap(const IteratorMap &source) : _position(source._position), _root(source._root) { }
				~IteratorMap() { }

				//////////////////////////////////Operators////////////////////////////////////////////

				IteratorMap			operator= (const IteratorMap &source) {
					this->_position = source._position;
					this->_root = source._root;
					return *this;
				}
				const_iterator		operator() () { return (const_iterator(*this)); }

				reference			operator* () { return _position->content; }
				pointer				operator-> () { return &_position->content; }

				//////////////////////////////////Accessors////////////////////////////////////////////

				node_pointer				base() const { return _position; }

				//////////////////////////////////Increment/Decrement//////////////////////////////////

				IteratorMap			&operator++ () {
					if (_position == NULL) {
						if (!_is_end)
							_position = _find_begin();
					}
					else if (_position->successor)
						_position = _position->successor;
					else {
						node_pointer tmp = _position;
						while (tmp->parent && *tmp <= *_position)
							tmp = tmp->parent;
						if (*tmp > *_position)
							_position = tmp;
						else {
							_position = NULL;
							_is_end = true;
						}
					}
					return *this;
				}
				IteratorMap			&operator++ (int) {
					IteratorMap		cp(*this);
					++(*this);
					return cp;
				}
				IteratorMap			&operator-- () {
					if (_position == NULL) {
						if (_is_end)
							_position = _find_last();
						_is_end = false;
					}
					else if (_position->predecessor)
						_position = _position->predecessor;
					else {
						node_pointer tmp = _position;
						while (tmp->parent && *tmp >= *_position)
							tmp = tmp->parent;
						if (*tmp < *_position)
							_position = tmp;
						else {
							_position = NULL;
							_is_end = false;
						}
					}
					return *this;
				}
				IteratorMap			&operator-- (int) {
					IteratorMap		cp(*this);
					--(*this);
					return cp;
				}
		};

	/////////////////////////////////Comparison Operators///////////////////////////////////////

	template<class Type, class TNode>
		bool	operator== (const IteratorMap<Type, TNode> &lhs, const IteratorMap<Type, TNode> &rhs) {
			return (lhs.base() == rhs.base());
		}
	template<class Type1, class Type2, class TNode>
		bool	operator== (const IteratorMap<Type1, TNode> &lhs, const IteratorMap<Type2, TNode> &rhs) {
			return (lhs.base() == rhs.base());
		}


	template<class Type, class TNode>
		bool	operator!= (const IteratorMap<Type, TNode> &lhs, const IteratorMap<Type, TNode> &rhs) {
			return (lhs.base() != rhs.base());
		}
	template<class Type1, class Type2, class TNode>
		bool	operator!= (const IteratorMap<Type1, TNode> &lhs, const IteratorMap<Type2, TNode> &rhs) {
			return (lhs.base() != rhs.base());
		}

}

#endif
