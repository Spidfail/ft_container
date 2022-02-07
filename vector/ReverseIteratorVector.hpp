/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseIteratorVector.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:49:49 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/07 21:49:50 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "IteratorVector.hpp"

namespace ft {

	template < class Iter >
		class ReverseIteratorVector {

			typedef					iterator_traits< Iter >							iterator_traits_type;

			public :
				typedef					Iter										iterator_type;
				typedef		typename	iterator_traits_type::difference_type		difference_type;
				typedef		typename	iterator_traits_type::value_type			value_type;
				typedef		typename	iterator_traits_type::pointer				pointer;
				typedef		typename	iterator_traits_type::reference				reference;
				typedef		typename	iterator_traits_type::iterator_category		iterator_category;

			private:
				Iter		_base_iterator;

			public:
				ReverseIteratorVector() : _base_iterator(NULL) { }
				ReverseIteratorVector(const iterator_type &it_source) : _base_iterator(it_source) { }
				ReverseIteratorVector(const ReverseIteratorVector &source) : _base_iterator(source._base_iterator) { }
				~ReverseIteratorVector() { }
				ReverseIteratorVector	&operator=(const ReverseIteratorVector &source) {
					this->_base_iterator = source._base_iterator;
					return *this;
				}

				/////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////OPERATORS///////////////////////////////////////////////
				//
				////////////////////////////////Member access////////////////////////////////////////////
				//
				iterator_type	base() const { return _base_iterator; }
				reference		operator[](difference_type index) { return _base_iterator[-index]; }
				reference		operator*() { return *_base_iterator; }
				pointer			operator->() { return _base_iterator; }

				////////////////////////////////Increment/Decrement//////////////////////////////////////
				//
				ReverseIteratorVector	&operator++(int) {
					_base_iterator--;
					return *this;
				}
				ReverseIteratorVector	operator++() {
					ReverseIteratorVector	cp(*this);
					_base_iterator--;
					return cp;
				}
				ReverseIteratorVector	&operator--(int) {
					_base_iterator++;
					return *this;
				}
				ReverseIteratorVector	operator--() {
					ReverseIteratorVector	cp(*this);
					_base_iterator++;
					return cp;
				}

				/////////////////////////////////Comparison Operators///////////////////////////////////////
				//
				friend bool	operator==(const ReverseIteratorVector &lhs, const ReverseIteratorVector &rhs) {
					return (lhs._base_iterator == rhs._base_iterator);
				}
				friend bool	operator!=(const ReverseIteratorVector &lhs, const ReverseIteratorVector &rhs) {
					return (lhs._base_iterator != rhs._base_iterator);
				}
				friend bool	operator<(const ReverseIteratorVector &lhs, const ReverseIteratorVector &rhs) {
					return (lhs._base_iterator > rhs._base_iterator);
				}
				friend bool	operator>(const ReverseIteratorVector &lhs, const ReverseIteratorVector &rhs) {
					return (lhs._base_iterator < rhs._base_iterator);
				}
				friend bool	operator<=(const ReverseIteratorVector &lhs, const ReverseIteratorVector &rhs) {
					return (lhs._base_iterator >= rhs._base_iterator);
				}
				friend bool	operator>=(const ReverseIteratorVector &lhs, const ReverseIteratorVector &rhs) {
					return (lhs._base_iterator <= rhs._base_iterator);
				}

				/////////////////////////////////Arithmetic Operators///////////////////////////////////////
				//
				friend ReverseIteratorVector	operator+(const ReverseIteratorVector &lhs, const int &n) {
					ReverseIteratorVector	cp(lhs._base_iterator - n);
					return cp;
				}
				friend ReverseIteratorVector	operator+(const int &n, const ReverseIteratorVector &lhs) {
					ReverseIteratorVector	cp(lhs._base_iterator - n);
					return cp;
				}
				friend ReverseIteratorVector	operator-(const ReverseIteratorVector &lhs, const int &n) {
					ReverseIteratorVector	cp(lhs._base_iterator + n);
					return cp;
				}
				friend long				operator-(const ReverseIteratorVector &lhs, const ReverseIteratorVector &rhs) {
					return rhs._base_iterator - lhs._base_iterator;
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
