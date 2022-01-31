/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseIteratorVector.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:49:49 by guhernan          #+#    #+#             */
/*   Updated: 2022/01/31 19:26:08 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "IteratorTraits.hpp"
#include <iterator>

namespace ft {

	template < typename T, class Allocator >
		class vector;

	template < typename T, class Allocator = std::allocator<T> >
		class ReverseIteratorVector {

			typedef		typename	ft::vector< T, Allocator >					container_type;

			public :
				typedef		typename	container_type::difference_type		difference_type;
				typedef		typename	container_type::value_type			value_type;
				typedef		typename	container_type::pointer				pointer;
				typedef		typename	container_type::reference			reference;
				typedef		typename	std::random_access_iterator_tag		iterator_category;

			private:
				pointer								_position;

			public:
				ReverseIteratorVector() : _position(NULL) { }
				ReverseIteratorVector(const pointer &pt_source) : _position(pt_source) { }
				ReverseIteratorVector(const ReverseIteratorVector &source) : _position(source._position) { }
				~ReverseIteratorVector() { }
				ReverseIteratorVector	&operator=(const ReverseIteratorVector &source) {
					this->_position = source._position;
					return *this;
				}

				/////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////OPERATORS///////////////////////////////////////////////
				//
				////////////////////////////////Member access////////////////////////////////////////////
				//
				reference		operator[](typename container_type::size_type index) { return _position[-index - 1]; }
				reference		operator*() { return *_position; }
				pointer			operator->() { return _position; }

				////////////////////////////////Increment/Decrement//////////////////////////////////////
				//
				ReverseIteratorVector	&operator++(int) {
					_position--;
					return *this;
				}
				ReverseIteratorVector	operator++() {
					ReverseIteratorVector	cp(*this);
					_position--;
					return cp;
				}
				ReverseIteratorVector	&operator--(int) {
					_position++;
					return *this;
				}
				ReverseIteratorVector	operator--() {
					ReverseIteratorVector	cp(*this);
					_position++;
					return cp;
				}

				/////////////////////////////////Comparison Operators///////////////////////////////////////
				//
				friend bool	operator==(const ReverseIteratorVector &lhs, const ReverseIteratorVector &rhs) {
					return (lhs._position == rhs._position);
				}
				friend bool	operator!=(const ReverseIteratorVector &lhs, const ReverseIteratorVector &rhs) {
					return (lhs._position != rhs._position);
				}
				friend bool	operator<(const ReverseIteratorVector &lhs, const ReverseIteratorVector &rhs) {
					return (lhs._position > rhs._position);
				}
				friend bool	operator>(const ReverseIteratorVector &lhs, const ReverseIteratorVector &rhs) {
					return (lhs._position < rhs._position);
				}
				friend bool	operator<=(const ReverseIteratorVector &lhs, const ReverseIteratorVector &rhs) {
					return (lhs._position >= rhs._position);
				}
				friend bool	operator>=(const ReverseIteratorVector &lhs, const ReverseIteratorVector &rhs) {
					return (lhs._position <= rhs._position);
				}

				/////////////////////////////////Arithmetic Operators///////////////////////////////////////
				//
				friend ReverseIteratorVector	operator+(const ReverseIteratorVector &lhs, const int &n) {
					ReverseIteratorVector	cp(lhs._position - n);
					return cp;
				}
				friend ReverseIteratorVector	operator+(const int &n, const ReverseIteratorVector &lhs) {
					ReverseIteratorVector	cp(lhs._position - n);
					return cp;
				}
				friend ReverseIteratorVector	operator-(const ReverseIteratorVector &lhs, const int &n) {
					ReverseIteratorVector	cp(lhs._position + n);
					return cp;
				}
				friend long				operator-(const ReverseIteratorVector &lhs, const ReverseIteratorVector &rhs) {
					return rhs._position - lhs._position;
				}

				/////////////////////////////////Assignation Operators//////////////////////////////////////
				//
				friend ReverseIteratorVector	&operator+=(ReverseIteratorVector &lhs, const int &n) {
					lhs = lhs + n;
					return lhs;
				}
				friend ReverseIteratorVector	&operator-=(ReverseIteratorVector &lhs, const int &n) {
					lhs = lhs - n;
					return lhs;
				}

		};
}

#endif
