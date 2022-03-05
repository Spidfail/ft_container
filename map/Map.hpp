

#ifndef MAP_HPP
# define MAP_HPP

# include <functional> 
# include "../Pair.hpp"

namespace ft {

	template <class Key,
			 class T,
			 class Compare = std::less<Key>,
			 class Alloc = std::allocator< ft::pair<const Key, T> > >


		class map {

			public:


				typedef		Key			key_type;
				typedef		T			mapped_type;
				typedef		ptrdiff_t	difference_type;
				typedef		Alloc		allocator_type;

				typedef 	pair<const key_type, mapped_type> 	value_type;

				typedef		size_t		size_type;

				typedef		value_type &		reference;
				typedef		const value_type &	const_reference;
				typedef		value_type *		pointer;
				typedef		const value_type *	const_pointer;

				typedef		Compare		key_compare;

				// typedef			iterator;
				// typedef			const_iterator;
				// typedef			reverse_iterator;
				// typedef			const_reverse_iterator;

			private:

			public:
				class value_compare;
				value_compare	value_comp() const {
					return value_compare(key_compare());
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
				value_compare(const value_compare &source) : _comp_instance(source._comp_instance) { }
				value_compare	operator() (const_reference value1, const_reference value2) const {
					return _comp_instance(value1.first, value2.first);
				}

		};


}

#endif
