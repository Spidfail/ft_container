/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:59:24 by guhernan          #+#    #+#             */
/*   Updated: 2022/01/21 22:20:12 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <memory>
#include <iostream>
#include <string>
#include <iterator>
#include <stdexcept>

namespace ft {

	template < typename T, class Allocator = std::allocator<T> >
		class vector {

			public:
				///////////////////////////////////////////////////////////////////////////////////////////////////
				///////////////////////////////////////////////////////////////////////////////////////////////////
				// Member types of Vector

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
				/////////////////////////////////////Member functions//////////////////////////////////////////////
				//
				//// CONSTRUCTORS

				 vector() :
					_start(NULL), _last(NULL), _size(0), _capacity(0), _alloc() {
					}

				explicit vector(const allocator_type &alloc) :
					_start(NULL), _last(NULL), _size(0), _capacity(0), _alloc(alloc) {
					}

				vector(const vector<value_type> &target, const allocator_type &alloc = allocator_type()) :
					_start(NULL), _last(NULL), _size(0), _capacity(0), _alloc(alloc) {
						*this = target;
					}

				vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) :
					_start(NULL), _last(NULL), _size(n), _capacity(n), _alloc(alloc) {
						this->_start = this->_alloc.allocate(n);
						for (size_type i = 0 ; i < n ; i++)
							this->_alloc.construct(this->_start + i, val);
						_set_members(_start, n, n);
					}

				~vector() {
					this->_erase_all();
					this->_start = NULL;
					this->_last = NULL;
					this->_end = NULL;
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////
				///////////////////////////////////////////////////////////////////////////////////////////////////
				//// MEMBERS OPERATORS
				//
				vector		&operator=(const vector<value_type> &source) {
					pointer		temp = _alloc.allocate(source.size());
					_copy(source.data(), source.data() + source.size(), temp);
					_erase_all();
					_set_members(temp, source.size(), source.size());
				}

				// See : Accessors for `operator[]`
				//
				///////////////////////////////////////////////////////////////////////////////////////////////////
				///////////////////////////////////////////////////////////////////////////////////////////////////
				//
				//// ACCESSORS : operator[], at(), front(), back(), data()
				//
				reference		operator[](size_type pos) {
					return *(this->_start + pos);
				}

				const_reference	operator[](size_type pos) const {
					return *(this->_start + pos);
				}

				reference		at(size_type pos) {
					if (pos < 0 || pos > _capacity)
						throw(std::out_of_range("Out of range"));    // Need to test the exception message
					return *(this->_start + pos);
				}

				const_reference	at(size_type pos) const {
					if (pos < 0 || pos > _capacity)
						throw(std::out_of_range("Out of range"));
					return *(this->_start + pos);
				}

				reference		front() {
					return *this->_start;
				}

				const_reference	front() const {
					return *this->_start;
				}

				reference		back() {
					return *this->_last;
				}

				const_reference	back() const {
					return *this->_last;
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////
				///////////////////////////////////////////////////////////////////////////////////////////////////
				//
				//// CAPACITY : empty(), size(), max_size(), reserve(), capacity()

				bool		empty() const {
					return !this->_size;
				}

				size_type	size() const {
					return this->_size;
				}

				void		reserve(size_type new_cap) {
					if (new_cap > _capacity) {
						pointer	temp = _alloc.allocate(new_cap);
						_copy(_start, _last, temp);
						_erase_all();
						_set_members(temp, new_cap, new_cap);
					}
					else if (new_cap > this->max_size()) {
						throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
					}
				}

				size_type	max_size() const throw() {
					return std::numeric_limits<size_type>::max() / sizeof(value_type);
				}

				size_type	capacity() const {
					return this->_capacity;
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////
				///////////////////////////////////////////////////////////////////////////////////////////////////
				//
				//// MODIFIERS: empty(), size(), max_size(), reserve(), capacity()

				void	assign(size_type count, const value_type &value) {
					pointer		temp = this->_alloc.allocate(count);
					_erase_all();
					for (size_type i = 0; i < count ; i++) {
						temp[i] = value;
					}
					_set_members(temp, count, count);
				}

				void push_back (const value_type& val) {

				}

				// void	assign() {      \\ iterator range version
				// }


			private:
				pointer			_start;
				pointer			_last;
				pointer			_end;
				size_type		_size;
				size_type		_capacity;
				allocator_type	_alloc;

				void			_copy(const pointer start, const pointer end, pointer target) const {
					for (size_type i = 0 ; start + i != end ; i++)
						target[i] = start[i];
				}

				void			_set_members(const pointer pointer, size_type size, size_type capacity) {
					this->_start = pointer;
					this->_last = pointer + size;
					this->_end = pointer + capacity;
					this->_size = size;
					this->_capacity = capacity;
				}

				void			_erase_all() {
					if (_start == NULL || _size == 0)
						return ;

					pointer		temp = _start;
					while (temp != _end) {
						_alloc.destroy(temp);
						temp++;
					}
					_alloc.deallocate(_start, _capacity);
				}

		};
}

#endif
