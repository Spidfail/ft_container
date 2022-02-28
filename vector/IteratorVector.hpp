/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IteratorVector.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:11:47 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/07 21:17:33 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORVECTOR_HPP
# define ITERATORVECTOR_HPP

# include "IteratorTraits.hpp"
# include "Iterator.hpp"

namespace ft {

	template < typename Category, typename T >
		class IteratorVector {

			typedef		typename	ft::iterator_traits< typename ft::iterator<Category, T> >	iterator_traits_type;

			public :
				typedef		typename	iterator_traits_type::difference_type		difference_type;
				typedef		typename	iterator_traits_type::value_type			value_type;
				typedef		typename	iterator_traits_type::pointer				pointer;
				typedef		typename	iterator_traits_type::reference				reference;
				typedef		typename	iterator_traits_type::iterator_category		iterator_category;

			private:
				typedef		IteratorVector<Category, const value_type>				const_iterator;
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
				////////////////////////////////Cast Operator////////////////////////////////////////////
				//
				operator const_iterator() { return const_iterator(this->_position); };
				//
				////////////////////////////////Member access////////////////////////////////////////////
				//
				reference		operator[](difference_type index) { return _position[index]; }
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
				friend bool	operator==(const IteratorVector<Category, T> &lhs, const IteratorVector<Category, T> &rhs) {
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
