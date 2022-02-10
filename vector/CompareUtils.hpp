/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CompareUtils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:13:35 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/09 16:57:34 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPAREUTILS_HPP ////////////////////////////////////////////////////////////////IFNDEF
# define COMPAREUTILS_HPP

#include "EnableIf.hpp"
#include "IsIntegral.hpp"

namespace ft {

	template <class InputIterator1, class InputIterator2>
		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2) {
			while (first1 != last1) {
				if (first2 == last2 || *first1 > *first2)
					return false;
				if (*first1 < *first2)
					return true;
				++first1, ++first2;
			}
			return (first1 == last1) && (first2 != last2);
		}

	template <class InputIterator1, class InputIterator2, class Compare>
		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2,
				Compare comp) {
			while (first1 != last1) {
				if (first2 == last2 || comp(*first2, *first1))
					return false;
				if (comp(*first1, *first2))
					return true;
				++first1, ++first2;
			}
			return first2 != last2;
		}

	//////////////////////////////////////////////////////////////////////////////
	template <class InputIterator1, class InputIterator2>
		bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2) {
			while (first1 != last1) {
				if (*first1 != *first2)
					return false;
				first1++, first2++;
			}
			return true;
		}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
		bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, BinaryPredicate pred) {
			while (first1 != last1) {
				if (!pred(*first1, *first2))
					return false;
				first1++, first2++;
			}
			return true;
		}

}

#endif//////////////////////////////////////////////////////////////////////////////////ENDIF
