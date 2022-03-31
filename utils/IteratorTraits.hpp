/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IteratorTraits.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:26:33 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/07 20:43:11 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORTRAITS_HPP
# define ITERATORTRAITS_HPP

#include <algorithm>
#include <cstddef>

namespace ft {

	template < class Iter >
		struct iterator_traits {
			typedef		typename	Iter::difference_type		difference_type;
			typedef		typename	Iter::value_type			value_type;
			typedef		typename	Iter::pointer				pointer;
			typedef		typename	Iter::reference				reference;
			typedef		typename	Iter::iterator_category		iterator_category;
		};

	template < class T >
		struct iterator_traits< T* > {
			typedef		std::ptrdiff_t						difference_type;
			typedef		T									value_type;
			typedef		T	*								pointer;
			typedef		T	&								reference;
			typedef		std::random_access_iterator_tag		iterator_category;
		};

	template < class T >
		struct iterator_traits< const T* > {
			typedef		std::ptrdiff_t						difference_type;
			typedef		T									value_type;
			typedef		const T	*							pointer;
			typedef		const T	&							reference;
			typedef		std::random_access_iterator_tag		iterator_category;
		};

}

#endif
