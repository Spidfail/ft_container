/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IteratorVector.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:11:47 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/02 23:00:45 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "IteratorTraits.hpp"
#include <iterator>

namespace ft {

	template < typename T, class Allocator >
		class vector;

	template < typename T, class Allocator = std::allocator<T> >
		class IteratorVector {

			typedef		typename	ft::vector< T, Allocator >					container_type;

			public :
				typedef		typename	container_type::difference_type		difference_type;
				typedef		typename	container_type::value_type			value_type;
				typedef		typename	container_type::pointer				pointer;
				typedef		typename	container_type::reference			reference;
				typedef		typename	std::random_access_iterator_tag		iterator_category;

			private:
				pointer		_position;

			public:
				IteratorVector() : _position(NULL) { }
				IteratorVector(const pointer &pt_source) : _position(pt_source) { }
				IteratorVector(const IteratorVector &source) : _position(source._position) { }
				~IteratorVector() { }
				IteratorVector	&operator=(const IteratorVector &source) {
					this->_position = source._position;
					return *this;
				}

				/////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////OPERATORS///////////////////////////////////////////////
				//
				////////////////////////////////Member access////////////////////////////////////////////
				//
				reference		operator[](typename container_type::size_type index) { return _position[index]; }
				reference		operator*() { return *_position; }
				pointer			operator->() { return _position; }

				////////////////////////////////Increment/Decrement//////////////////////////////////////
				//
				IteratorVector	&operator++(int) {
					_position++;
					return *this;
				}
				IteratorVector	operator++() {
					IteratorVector	cp(*this);
					_position++;
					return cp;
				}
				IteratorVector	&operator--(int) {
					_position--;
					return *this;
				}
				IteratorVector	operator--() {
					IteratorVector	cp(*this);
					_position--;
					return cp;
				}

				/////////////////////////////////Comparison Operators///////////////////////////////////////
				//
				friend bool	operator==(const IteratorVector &lhs, const IteratorVector &rhs) {
					return (lhs._position == rhs._position);
				}
				friend bool	operator!=(const IteratorVector &lhs, const IteratorVector &rhs) {
					return (lhs._position != rhs._position);
				}
				friend bool	operator<(const IteratorVector &lhs, const IteratorVector &rhs) {
					return (lhs._position < rhs._position);
				}
				friend bool	operator>(const IteratorVector &lhs, const IteratorVector &rhs) {
					return (lhs._position > rhs._position);
				}
				friend bool	operator<=(const IteratorVector &lhs, const IteratorVector &rhs) {
					return (lhs._position <= rhs._position);
				}
				friend bool	operator>=(const IteratorVector &lhs, const IteratorVector &rhs) {
					return (lhs._position >= rhs._position);
				}

				/////////////////////////////////Arithmetic Operators///////////////////////////////////////
				//
				friend IteratorVector	operator+(const IteratorVector &lhs, const int &n) {
					IteratorVector	cp(lhs._position + n);
					return cp;
				}
				friend IteratorVector	operator+(const int &n, const IteratorVector &lhs) {
					IteratorVector	cp(n + lhs._position);
					return cp;
				}
				friend IteratorVector	operator-(const IteratorVector &lhs, const int &n) {
					IteratorVector	cp(lhs._position - n);
					return cp;
				}
				friend long				operator-(const IteratorVector &lhs, const IteratorVector &rhs) {
					return lhs._position - rhs._position;
				}

				/////////////////////////////////Assignation Operators//////////////////////////////////////
				//
				friend IteratorVector	&operator+=(IteratorVector &lhs, const int &n) {
					lhs = lhs + n;
					return lhs;
				}
				friend IteratorVector	&operator-=(IteratorVector &lhs, const int &n) {
					lhs = lhs - n;
					return lhs;
				}

		};
}

#endif
