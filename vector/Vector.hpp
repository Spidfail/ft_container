/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:59:24 by guhernan          #+#    #+#             */
/*   Updated: 2022/01/31 18:36:57 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <memory>
#include <iostream>
#include <string>
#include <iterator>
#include <stdexcept>
#include <algorithm>

#include "IteratorVector.hpp"
#include "ReverseIteratorVector.hpp"

namespace ft {

	template < typename T, class Allocator = std::allocator<T> >
		class vector {

			public:
				/////////////////////////////////////Member type////////////////////////////////////////////
				// Member types of Vector

				typedef				T																value_type;
				typedef				Allocator														allocator_type;
				typedef				std::size_t														size_type;
				typedef				std::ptrdiff_t													difference_type;
				typedef				value_type&														reference;
				typedef				const value_type&												const_reference;
				typedef	typename	Allocator::pointer												pointer;
				typedef	typename	Allocator::const_pointer										const_pointer;
				typedef				ft::IteratorVector<value_type, allocator_type>					iterator;
				typedef				const ft::IteratorVector<value_type, allocator_type>			const_iterator;
				typedef				ft::ReverseIteratorVector<value_type, allocator_type>			reverse_iterator;
				typedef				const ft::ReverseIteratorVector<value_type, allocator_type>		const_reverse_iterator;

			private:
				pointer			_start;
				pointer			_last;
				pointer			_end;
				size_type		_size;
				size_type		_capacity;
				allocator_type	_alloc;

				//////////////////////////////Private Member Methods////////////////////////////////////////

				void			_copy( const pointer start, const pointer end, pointer target ) const {
					for (size_type i = 0 ; start + i != end ; i++)
						target[i] = start[i];
				}

				void			_set_members( const pointer pointer, size_type size, size_type capacity ) {
					this->_start = pointer;
					this->_last = pointer + size;
					this->_end = pointer + capacity;
					this->_size = size;
					this->_capacity = capacity;
				}

				void			_set_size( size_type new_size ) {
					if (new_size <= _capacity)
						_set_members(_start, new_size, _capacity);
				}

				void			_set_capacity( size_type new_capacity ) {
					if (new_capacity >= _size)
						_set_members(_start, _capacity, new_capacity);
				}

				void			_reset_members() {
					this->_start = NULL;
					this->_last = NULL;
					this->_end = NULL;
					this->_size = 0;
					this->_capacity = 0;
				}

				void			_destroy(pointer pos, size_type n = 1) {
					if (pos - _start + (n - 1) > _size)
						return ;
					while (pos != _start + n && pos != _last)
						_alloc.destroy(pos++);
				}

				void			_destroy_all() {
					for (pointer temp = _start ; temp != _end ; temp++)
						_alloc.destroy(temp);
				}

				void			_erase_all() {
					if (_start == NULL || _size == 0)
						return ;
					_destroy_all();
					_alloc.deallocate(_start, _capacity);
					_reset_members();
				}

			public:
				/////////////////////////////////////Member functions///////////////////////////////////////
				//// CONSTRUCTORS
				 vector() :
					_start(NULL), _last(NULL), _size(0), _capacity(0), _alloc() { }

				explicit vector( const allocator_type &alloc ) :
					_start(NULL), _last(NULL), _size(0), _capacity(0), _alloc(alloc) { }

				vector( const vector<value_type> &target, const allocator_type &alloc = allocator_type() ) :
					_start(NULL), _last(NULL), _size(0), _capacity(0), _alloc(alloc) { *this = target; }

				vector( size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type() ) :
					_start(NULL), _last(NULL), _size(n), _capacity(n), _alloc(alloc) {
						this->_start = this->_alloc.allocate(n);
						for (size_type i = 0 ; i < n ; i++)
							this->_alloc.construct(this->_start + i, val);
						_set_members(_start, n, n);
					}

				~vector() {
					this->_erase_all();
					_reset_members();
				}

				////////////////////////////////////////////////////////////////////////////////////////////
				//// MEMBERS OPERATORS

				vector		&operator=( const vector<value_type> &source ) {
					pointer		temp = _alloc.allocate(source.size());
					_copy(source._start, source._start + source.size(), temp);
					_erase_all();
					_set_members(temp, source.size(), source.size());
					return *this;
				}

				// See : Accessors for `operator[]`
				//
				////////////////////////////////////////////////////////////////////////////////////////////
				//// ACCESSORS : operator[], at(), front(), back(), data()

				reference		operator[]( size_type pos ) { return *(this->_start + pos); }
				const_reference	operator[]( size_type pos ) const { return *(this->_start + pos); }

				reference		at( size_type pos ) {
					if (pos < 0 || pos > _capacity)
						throw(std::out_of_range("Out of range"));    // Need to test the exception message
					return *(this->_start + pos);
				}
				const_reference	at( size_type pos ) const {
					if (pos < 0 || pos > _capacity)
						throw(std::out_of_range("Out of range"));
					return *(this->_start + pos);
				}

				reference		front() { return *this->_start; }
				const_reference	front() const { return *this->_start; }

				reference		back() { return *this->_last; }
				const_reference	back() const { return *this->_last; }

				////////////////////////////////////////////////////////////////////////////////////////////
				//// ITERATOS : begin, end(), rbegin(), rend()
				//
				iterator begin() { return iterator(_start); }
				const iterator begin() const { return iterator(_start); }
				
				iterator end() { return iterator(_end); }
				const iterator end() const { return iterator(_end); }

				reverse_iterator rbegin() { return reverse_iterator(_end - 1); }
				const iterator rbegin() const { return reverse_iterator(_end - 1); }

				reverse_iterator rend() { return reverse_iterator(_start - 1); }
				const iterator rend() const { return reverse_iterator(_start - 1); }

				////////////////////////////////////////////////////////////////////////////////////////////
				//// CAPACITY : empty(), size(), max_size(), reserve(), capacity()

				bool		empty() const { return !this->_size; }

				size_type	size() const { return this->_size; }

				void		reserve( size_type new_cap ) {
					if (new_cap > this->max_size()) {
						throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
					}
					if (new_cap > _capacity) {
						size_type	tmp_size = _size;
						pointer	temp = _alloc.allocate(new_cap);
						_copy(_start, _last, temp);
						_erase_all();
						_set_members(temp, tmp_size, new_cap);
					}
				}

				size_type	max_size() const throw() { return std::numeric_limits<size_type>::max() / sizeof(value_type); }

				size_type	capacity() const { return this->_capacity; }

				////////////////////////////////////////////////////////////////////////////////////////////
				//// MODIFIERS: empty(), size(), max_size(), reserve(), capacity()

				void	assign( size_type count, const value_type &value ) {
					pointer		temp = this->_alloc.allocate(count);
					_erase_all();
					for (size_type i = 0; i < count ; i++) {
						temp[i] = value;
					}
					_set_members(temp, count, count);
				}

				// template< class InputIt >								// Iterator form
					// void assign( InputIt first, InputIt last );

				void	clear() {
					_destroy_all();
					_set_size(0);
				}

				// insert ()

				iterator erase( iterator pos ) {
					_destroy(pos);
					while (pos != _end)
						pos = pos + 1;
					_set_size(_size - 1);
				}

				void	push_back( const T& value ) {
					if (_capacity == 0)
						this->reserve(1);
					else if (_size + 1 > _capacity)
						this->reserve(_capacity * 2);
					_start[_size] = value;
					_set_size(_size + 1);
				}

				void	pop_back() {
					_alloc.destroy(_last);
					_set_size(_size - 1);
				}

				void swap( vector& other ) {
					std::swap(this->_start, other._start);
					std::swap(this->_last, other._last);
					std::swap(this->_end, other._end);
					std::swap(this->_size, other._size);
					std::swap(this->_capacity, other._capacity);
					// Could be done by bitwise operation XOR, in one line :
					// (other._start ^= this->_start), (this->_start ^= other._start),
						// (other._start ^= this->_start);
				}

				void	resize( size_type count, T value = T() ) {
					if (count > _size) {
						if (count > _capacity)
							this->reserve(count);
						for (pointer pt = _last ; pt != _last + count ; pt++)
							pt = value;
					}
						// miss erase for the rest
				}

				////////////////////////////////////////////////////////////////////////////////////////////
				//// ALLOCATOR: get_allocator

				allocator_type get_allocator() const { return _alloc; }

		};

}

namespace std {
	template <class T, class Alloc>
		void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y) {
			x.swap(y);
		}
}


#endif
