
#ifndef NODE_HPP
# define NODE_HPP

# include <functional>
# include "../Pair.hpp"

namespace ft {


	template <typename T, class VCompare >
		struct Node {
			typedef		T				value_type;
			typedef		T	&			reference;
			typedef		const T	&		const_reference;
			typedef		T	*			pointer;
			typedef		const T	*		const_pointer;
			typedef		VCompare		value_compare;

			Node		*parent;
			Node		*predecessor;
			Node		*successor;
			value_type	content;
			short int	balance_factor;

			Node() :
				parent(NULL), predecessor(NULL), successor(NULL), content(), balance_factor(0) { }
			Node(const Node &source) :
				parent(source.parent), predecessor(source.predecessor), successor(source.successor),
				content(source.content), balance_factor(source.balance_factor) { }
			Node(const_reference value) :
				parent(NULL), predecessor(NULL), successor(NULL), content(value), balance_factor(0) { }
			Node(const_reference value, Node *parent) :
				parent(parent), predecessor(NULL), successor(NULL), content(value), balance_factor(0) { }
			Node	operator=(const Node &source) {
				parent = source.parent;
				predecessor = source.parent;
				successor = source.parent;
				content = source.content;
				balance_factor = source.balance_factor;
				return *this;
			}
			~Node() {
				parent = NULL;
				predecessor = NULL;
				successor = NULL;
				balance_factor = 0;
			}
		};

	template<class Type, class VCompare>
		bool	operator<(const Node<Type, VCompare> &lhs, const Node<Type, VCompare> &rhs) {
			return (typename Node<Type, VCompare>::value_compare()(lhs.content, rhs.content));
		}

	template<class Type, class VCompare>
		bool	operator>(const Node<Type, VCompare> &lhs, const Node<Type, VCompare> &rhs) {
			return (!(lhs == rhs) && !(lhs < rhs));
		}

	template<class Type, class VCompare>
		bool	operator<=(const Node<Type, VCompare> &lhs, const Node<Type, VCompare> &rhs) {
			return (lhs < rhs || (lhs == rhs));
		}

	template<class Type, class VCompare>
		bool	operator>=(const Node<Type, VCompare> &lhs, const Node<Type, VCompare> &rhs) {
			return (!(lhs < rhs));
		}

	template<class Type, class VCompare>
		bool	operator==(const Node<Type, VCompare> &lhs, const Node<Type, VCompare> &rhs) {
			return (lhs.content.first == rhs.content.first);
		}

	template<class Type, class VCompare>
		bool	operator!=(const Node<Type, VCompare> &lhs, const Node<Type, VCompare> &rhs) {
			return (!(lhs == rhs));
		}



}
#endif
