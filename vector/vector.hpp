/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:59:24 by guhernan          #+#    #+#             */
/*   Updated: 2022/01/11 20:05:22 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <iostream>
#include <string>
#include <iterator>

template <class T, class Allocator = std::allocator<T> >
class ft_vector {

	public:

	// Member types of Vector
	//
		typedef				T													value_type;
		typedef				Allocator											allocator_type;
		typedef				std::size_t											size_type;
		typedef				std::ptrdiff_t										difference_type;

		typedef				value_type&											reference;
		typedef				const value_type&									const_reference;

		typedef	typename	Allocator::pointer									pointer;
		typedef	typename	Allocator::const_pointer							const_pointer;

		typedef				std::iterator<value_type, allocator_type>			iterator;
		typedef				const std::iterator<value_type, allocator_type>		const_iterator;
		typedef				std::reverse_iterator<iterator>						reverse_iterator;
		typedef				const std::reverse_iterator<iterator>				const_reverse_iterator;


	// Member functions
	//
	// construct start with size 0
		ft_vector() {
			allocator_type	alloc;
			alloc.
		};


		~ft_vector() {
		};




};
