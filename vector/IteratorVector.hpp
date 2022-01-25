/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IteratorVector.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:11:47 by guhernan          #+#    #+#             */
/*   Updated: 2022/01/25 21:16:57 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "IteratorTraits.hpp"
#include "Vector.hpp"
#include <iterator>


namespace ft {

	template < typename T  >
		class IteratorVector {

			typedef		typename	ft::vector< T >					container_type;

			public :
				typedef		typename	container_type::difference_type		difference_type;
				typedef		typename	container_type::value_type			value_type;
				typedef		typename	container_type::pointer				pointer;
				typedef		typename	container_type::reference			reference;
				typedef		typename	std::random_access_iterator_tag		iterator_category;

			private:
				pointer		_position;
				friend bool					operator==(const IteratorVector<T> &lhs, const IteratorVector<T> &rhs);
				friend bool					operator!=(const IteratorVector<T> &lhs, const IteratorVector<T> &rhs);
				friend bool					operator<(const IteratorVector<T> &lhs, const IteratorVector<T> &rhs);
				friend bool					operator>(const IteratorVector<T> &lhs, const IteratorVector<T> &rhs);
				friend bool					operator<=(const IteratorVector<T> &lhs, const IteratorVector<T> &rhs);
				friend bool					operator>=(const IteratorVector<T> &lhs, const IteratorVector<T> &rhs);

				friend IteratorVector<T>	operator+(const IteratorVector<T> &lhs, const int &n);
				friend IteratorVector<T>	operator+(const int &n, const IteratorVector<T> &lhs);
				friend IteratorVector<T>	operator-(const IteratorVector<T> &lhs, const int &n);
				friend IteratorVector<T>	operator-(const IteratorVector<T> &lhs, const IteratorVector<T> &rhs);

			public:
				IteratorVector() : _position(NULL) { }

				IteratorVector(const IteratorVector &source) : _position(source._position) { }

				~IteratorVector() { }

				IteratorVector	&operator=(const IteratorVector &source) {
					this->_position = source._position;
				}

				/////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////OPERATORS///////////////////////////////////////////////
				//
				////////////////////////////////Member access////////////////////////////////////////////
				//
				reference		operator[](typename container_type::size_type index) {
					return _position[index];
				}

				reference		operator*() {
					return *_position;
				}

				pointer			operator->() {
					return _position;
				}
				////////////////////////////////Increment/Decrement//////////////////////////////////////
				//
				IteratorVector	&operator++(int) {
					_position++;
					return *this;
				}

				IteratorVector	operator++() {
					IteratorVector	new_it(this);
					_position++;
					return new_it;
				}

				IteratorVector	&operator--(int) {
					_position--;
					return *this;
				}

				IteratorVector	operator--() {
					IteratorVector	cp(this);
					_position--;
					return cp;
				}

		};

	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////COMPARISON OPERATORS///////////////////////////////////////////////
	//
	template < typename T >
	bool	operator==(const IteratorVector<T> &lhs, const IteratorVector<T> &rhs) {
		return (lhs._position == rhs._position);
	}

	template < typename T >
	bool	operator!=(const IteratorVector<T> &lhs, const IteratorVector<T> &rhs) {
		return (lhs._position != rhs._position);
	}

	template < typename T >
	bool	operator<(const IteratorVector<T> &lhs, const IteratorVector<T> &rhs) {
		return (lhs._position < rhs._position);
	}

	template < typename T >
	bool	operator>(const IteratorVector<T> &lhs, const IteratorVector<T> &rhs) {
		return (lhs._position > rhs._position);
	}

	template < typename T >
	bool	operator<=(const IteratorVector<T> &lhs, const IteratorVector<T> &rhs){
		return (lhs._position <= rhs._position);
	}

	template < typename T >
	bool	operator>=(const IteratorVector<T> &lhs, const IteratorVector<T> &rhs){
		return (lhs._position >= rhs._position);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////COMPARISON OPERATORS///////////////////////////////////////////////
	//
	template < typename T >
	IteratorVector<T>	operator+(const IteratorVector<T> &lhs, const int &n) {
		IteratorVector<T>	cp(lhs._position + n);
		return cp;
	}

	template < typename T >
	IteratorVector<T>	operator+(const int &n, const IteratorVector<T> &lhs) {
		IteratorVector<T>	cp(lhs._position + n);
		return cp;
	}

	template < typename T >
	IteratorVector<T>	operator-(const IteratorVector<T> &lhs, const int &n) {
		IteratorVector<T>	cp(lhs._position - n);
		return cp;
	}

	template < typename T >
	IteratorVector<T>	operator-(const IteratorVector<T> &lhs, const IteratorVector<T> &rhs) {
		IteratorVector<T>	cp(lhs._position - rhs._position);
	}


	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////ASSIGNATION OPERATORS///////////////////////////////////////////////
	//
	template < typename T >
	IteratorVector<T>	&operator+=(IteratorVector<T> &lhs, const int &n) {
		lhs = lhs + n;
		return lhs;
	}

	template < typename T >
	IteratorVector<T>	&operator-=(IteratorVector<T> &lhs, const int &n) {
		lhs = lhs - n;
		return lhs;
	}
}

#endif
