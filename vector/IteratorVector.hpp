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

# include "../IteratorTraits.hpp"
# include "../Iterator.hpp"

namespace ft {

	template < typename T >
		class IteratorVector {

			typedef		typename	ft::iterator_traits< typename ft::iterator<std::random_access_iterator_tag, T> >	iterator_traits_type;

			public :
				typedef		typename	iterator_traits_type::difference_type		difference_type;
				typedef		typename	iterator_traits_type::value_type			value_type;
				typedef		typename	iterator_traits_type::pointer				pointer;
				typedef		typename	iterator_traits_type::reference				reference;
				typedef		typename	iterator_traits_type::iterator_category		iterator_category;

			private:
				typedef		IteratorVector<const value_type>						const_iterator;
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
				////////////////////////////////PUBLIC METHODS///////////////////////////////////////////
				//
				pointer		base() const { return _position; }
				

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

				/////////////////////////////////Arithmetic Operators///////////////////////////////////////
				//
				friend IteratorVector	operator+(const IteratorVector &lhs, const difference_type &n) {
					IteratorVector	cp(lhs._position + n);
					return cp;
				}
				friend IteratorVector	operator+(const difference_type &n, const IteratorVector &lhs) {
					IteratorVector	cp(n + lhs._position);
					return cp;
				}
				friend IteratorVector	operator-(const IteratorVector &lhs, const difference_type &n) {
					IteratorVector	cp(lhs._position - n);
					return cp;
				}

				/////////////////////////////////Assignation Operators//////////////////////////////////////
				//
				friend IteratorVector	&operator+=(IteratorVector &lhs, const difference_type &n) {
					lhs = lhs + n;
					return lhs;
				}
				friend IteratorVector	&operator-=(IteratorVector &lhs, const difference_type &n) {
					lhs = lhs - n;
					return lhs;
				}

		};


	/////////////////////////////////Arithmetic Operators///////////////////////////////////////
	//
	template<class Type>
		long				operator-(const ft::IteratorVector<Type> &lhs, const ft::IteratorVector<Type> &rhs) {
			return lhs.base() - rhs.base();
		}
	template<class Type1, class Type2>
		long				operator-(const ft::IteratorVector<Type1> &lhs, const ft::IteratorVector<Type2> &rhs) {
			return lhs.base() - rhs.base();
		}

	/////////////////////////////////Comparison Operators///////////////////////////////////////
	//
	template<class Type>
		bool	operator==(const ft::IteratorVector<Type> &lhs, const ft::IteratorVector<Type> &rhs) {
			return (lhs.base() == rhs.base());
		}
	template<class Type1, class Type2>
		bool	operator==(const ft::IteratorVector<Type1> &lhs, const ft::IteratorVector<Type2> &rhs) {
			return (lhs.base() == rhs.base());
		}

	template<class Type>
		bool	operator!=(const ft::IteratorVector<Type> &lhs, const ft::IteratorVector<Type> &rhs) {
			return (lhs.base() != rhs.base());
		}
	template<class Type1, class Type2>
		bool	operator!=(const ft::IteratorVector<Type1> &lhs, const ft::IteratorVector<Type2> &rhs) {
			return (lhs.base() != rhs.base());
		}

	template<class Type>
		bool	operator<(const ft::IteratorVector<Type> &lhs, const ft::IteratorVector<Type> &rhs) {
			return (lhs.base() < rhs.base());
		}
	template<class Type1, class Type2>
		bool	operator<(const ft::IteratorVector<Type1> &lhs, const ft::IteratorVector<Type2> &rhs) {
			return (lhs.base() < rhs.base());
		}

	template<class Type>
		bool	operator>(const ft::IteratorVector<Type> &lhs, const ft::IteratorVector<Type> &rhs) {
			return (lhs.base() > rhs.base());
		}
	template<class Type1, class Type2>
		bool	operator>(const ft::IteratorVector<Type1> &lhs, const ft::IteratorVector<Type2> &rhs) {
			return (lhs.base() > rhs.base());
		}

	template<class Type>
		bool	operator<=(const ft::IteratorVector<Type> &lhs, const ft::IteratorVector<Type> &rhs) {
			return (lhs.base() <= rhs.base());
		}
	template<class Type1, class Type2>
		bool	operator<=(const ft::IteratorVector<Type1> &lhs, const ft::IteratorVector<Type2> &rhs) {
			return (lhs.base() <= rhs.base());
		}

	template<class Type>
		bool	operator>=(const ft::IteratorVector<Type> &lhs, const ft::IteratorVector<Type> &rhs) {
			return (lhs.base() >= rhs.base());
		}
	template<class Type1, class Type2>
		bool	operator>=(const ft::IteratorVector<Type1> &lhs, const ft::IteratorVector<Type2> &rhs) {
			return (lhs.base() >= rhs.base());
		}

}

#endif
