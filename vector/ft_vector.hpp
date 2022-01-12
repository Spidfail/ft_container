/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:59:24 by guhernan          #+#    #+#             */
/*   Updated: 2022/01/12 20:31:59 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <memory>
#include <iostream>
#include <string>
#include <iterator>
#include <stdexcept>

template < typename T, class Allocator = std::allocator<T> >
class FtVector {

	public:
	///////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////
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


	///////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// //////////////////////////////////Member functions//////////////////////////////////////////////
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//// CONSTRUCTORS
	//
		explicit FtVector(const allocator_type &alloc = allocator_type()) :
				_start(NULL), _last(NULL), _size(0), _capacity(0), _alloc(alloc) {
		}

		FtVector(const FtVector<value_type> &target) :
				_start(NULL), _last(NULL), _size(0), _capacity(0) {

			*this = target;
		}

		FtVector(const size_type &n, const value_type &val = value_type(),
				const allocator_type &alloc = allocator_type()) :
				_start(NULL), _last(NULL), _size(n), _capacity(n), _alloc(alloc) {

			this->_start = this->_alloc.allocate(n);
			for (size_type i = 0 ; i < n ; i++) {
				this->_alloc.construct(this->_start + i, val);
			}
			this->_last = this->start + n;
		}


		~FtVector() {
		}

	///////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//// OPERATORS
	//
		FtVector		&operator=(const FtVector<value_type> &) {

		}

		reference		operator[](size_type pos) {
			return this->_start + pos;
		}

		const_reference	operator[](size_type pos) const {
			return this->_start + pos;
		}
	///////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//// ACCESSORS : at(), front(), back(), data()
	//
		reference		at(size_type pos) {
			if (pos < 0 || pos > _capacity)
				throw(std::out_of_range("Out of range"));
			return &this->_start + pos;
		}

		const_reference	at(size_type pos) const {
			if (pos < 0 || pos > _capacity)
				throw(std::out_of_range("Out of range"));
			return &this->_start + pos;
		}

		reference		front() {
			return &this->_start;
		}

		const_reference	front() const {
			return &this->_start;
		}

		reference		back() {
			return &this->_last;
		}

		const_reference	back() const {
			return &this->_last;
		}

		pointer			data() {
			return this->_start;
		}

		const_pointer	data() const {
			return this->_start;
		}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//// CAPACITY : empty(), size(), max_size(), reserve(), capacity()
	
		bool		empty() const {
			return this->size;
		}

		size_type	size() const {
			return this->size;
		}

		// size_type	max_size() const {
		// }

		void		reserve(size_type new_cap) {
		}


	private:

		pointer			_start;
		pointer			_last;

		size_type		_size;
		size_type		_capacity;

		allocator_type	_alloc;

};

#endif
