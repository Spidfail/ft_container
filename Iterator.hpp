
#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft {

	template < typename Category, typename T >
		struct iterator {
			typedef		Category	iterator_category;
			typedef		T			value_type;
			typedef		ptrdiff_t	difference_type;
			typedef		T*			pointer;
			typedef		T&			reference;
		};

}

#endif
