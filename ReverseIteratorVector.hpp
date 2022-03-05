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

# include "IteratorTraits.hpp"

namespace ft {

	template < class Iter >
		class ReverseIterator {

			typedef					iterator_traits<Iter>						iterator_traits_type;
			typedef					ReverseIterator<Iter>						reverse_iterator;

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
				ReverseIterator() : _base_iterator(NULL) { }
				ReverseIterator(const iterator_type &it_source) : _base_iterator(it_source) { }
				ReverseIterator(const ReverseIterator &source) : _base_iterator(source._base_iterator) { }
				~ReverseIterator() { }

				template<class Iterator>
				ReverseIterator &operator= (const ReverseIterator<Iterator> &source)
				{
					this->_base_iterator = source._base_iterator;
					return *this;
				}

				iterator_type	base() const { return _base_iterator; }

				/////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////OPERATORS///////////////////////////////////////////////
				////////////////////////////////Cast operator////////////////////////////////////////////
				//
				template <typename TConst>
				operator	ReverseIterator<TConst>() { return ReverseIterator<TConst>(this->base()); }
				////////////////////////////////Member access////////////////////////////////////////////
				//
				reference		operator[](difference_type index) { return _base_iterator[-index]; }
				reference		operator*() { return *_base_iterator; }
				pointer			operator->() { return _base_iterator; }

				////////////////////////////////Increment/Decrement//////////////////////////////////////
				//
				reverse_iterator	&operator++(int) {
					--_base_iterator;
					return *this;
				}
				reverse_iterator	operator++() {
					reverse_iterator	cp(*this);
					--_base_iterator;
					return cp;
				}
				reverse_iterator	&operator--(int) {
					++_base_iterator;
					return *this;
				}
				reverse_iterator	operator--() {
					reverse_iterator	cp(*this);
					++_base_iterator;
					return cp;
				}


				/////////////////////////////////Arithmetic Operators///////////////////////////////////////
				//
				template<class Iterator>
				friend ReverseIterator	operator+(const ReverseIterator<Iterator> &lhs, const difference_type &n) {
					ReverseIterator	cp(lhs._base_iterator - n);
					return cp;
				}
				template<class Iterator>
				friend ReverseIterator	operator+(const difference_type &n, const ReverseIterator<Iterator> &lhs) {
					ReverseIterator	cp(lhs._base_iterator - n);
					return cp;
				}
				template<class Iterator>
				friend ReverseIterator	operator-(const ReverseIterator<Iterator> &lhs, const difference_type &n) {
					ReverseIterator	cp(lhs._base_iterator + n);
					return cp;
				}

				/////////////////////////////////Assignation Operators//////////////////////////////////////
				//
				template<class Iterator>
				friend ReverseIterator	&operator+=(ReverseIterator<Iterator> &lhs, const difference_type &n) {
					lhs = lhs + n;
					return lhs;
				}
				template<class Iterator>
				friend ReverseIterator	&operator-=(ReverseIterator<Iterator> &lhs, const difference_type &n) {
					lhs = lhs - n;
					return lhs;
				}

		};

	/////////////////////////////////Arithmetic Operators///////////////////////////////////////
	//
	template<class Iterator>
		long	operator-(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs) {
			return rhs.base() - lhs.base();
		}
	template<class Iterator1, class Iterator2>
		long	operator-(const ReverseIterator<Iterator1> &lhs, const ReverseIterator<Iterator2> &rhs) {
			return rhs.base() - lhs.base();
		}

	/////////////////////////////////Comparison Operators///////////////////////////////////////
	//
	template<class Iterator>
		bool	operator==(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs) {
			return (lhs.base() == rhs.base());
		}
	template<class Iterator1, class Iterator2>
		bool	operator==(const ReverseIterator<Iterator1> &lhs, const ReverseIterator<Iterator2> &rhs) {
			return (lhs.base() == rhs.base());
		}

	template<class Iterator>
		bool	operator!=(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs) {
			return (lhs.base() != rhs.base());
		}
	template<class Iterator1, class Iterator2>
		bool	operator!=(const ReverseIterator<Iterator1> &lhs, const ReverseIterator<Iterator2> &rhs) {
			return (lhs.base() != rhs.base());
		}


	template<class Iterator>
		bool	operator<(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs) {
			return (lhs.base() > rhs.base());
		}
	template<class Iterator1, class Iterator2>
		bool	operator<(const ReverseIterator<Iterator1> &lhs, const ReverseIterator<Iterator2> &rhs) {
			return (lhs.base() > rhs.base());
		}

	template<class Iterator>
		bool	operator>(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs) {
			return (lhs.base() < rhs.base());
		}
	template<class Iterator1, class Iterator2>
		bool	operator>(const ReverseIterator<Iterator1> &lhs, const ReverseIterator<Iterator2> &rhs) {
			return (lhs.base() < rhs.base());
		}


	template<class Iterator>
		bool	operator<=(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs) {
			return (lhs.base() >= rhs.base());
		}
	template<class Iterator1, class Iterator2>
		bool	operator<=(const ReverseIterator<Iterator1> &lhs, const ReverseIterator<Iterator2> &rhs) {
			return (lhs.base() >= rhs.base());
		}

	template<class Iterator>
		bool	operator>=(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs) {
			return (lhs.base() <= rhs.base());
		}
	template<class Iterator1, class Iterator2>
		bool	operator>=(const ReverseIterator<Iterator1> &lhs, const ReverseIterator<Iterator2> &rhs) {
			return (lhs.base() <= rhs.base());
		}

}

#endif
