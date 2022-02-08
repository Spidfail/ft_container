/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIteratorsTests.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:22:33 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/08 12:23:57 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATORSTESTS_HPP ///////////////////////////////////////////////////////////////// IFNDEF
# define VECTORITERATORSTESTS_HPP

#include <iostream>

namespace ft {

		template <class Ct, typename Os, typename type_value>
		struct UnitestIterators {

			typedef typename Ct::size_type	size_type;

			static void		constructors(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vecfill(10, random_value);
					typename Ct::iterator it;
					it = vecfill.begin();
					Ct	vecfill2(20, replacement);
					vecfill = vecfill2;
					typename Ct::iterator it2 = vecfill.begin();
					os << std::boolalpha << (it == it2) << " ";
				} {
					Ct	vecfill(10, random_value);
					typename Ct::reverse_iterator it;
					it = vecfill.rbegin();
					Ct	vecfill2(20, replacement);
					vecfill = vecfill2;
					typename Ct::reverse_iterator it2 = vecfill.rbegin();
					os << std::boolalpha << (it == it2) << " ";
					typename Ct::reverse_iterator it3(vecfill2.begin());
					os << std::boolalpha << (it3 == it2) << " ";
				}
				os << std::endl;
			}

			static void		accessors(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vecfill(1, random_value);
					vecfill.push_back(replacement);
					typename Ct::iterator it = vecfill.begin();
					typename Ct::iterator it2 = it;
					os << *it << "|" << *it2;
				} {
					Ct	vecfill(10, random_value);
					typename Ct::iterator it = vecfill.begin();
					for (size_type i = 0 ; i < vecfill.size() ; i++){ os << it[i] << " "; }
					for (size_type i = 0 ; i < vecfill.size() ; i++){ os << (it[i] = replacement) << " "; }
				} {
					Ct	vecfill(1, random_value);
					vecfill.push_back(replacement);
					typename Ct::reverse_iterator it = vecfill.rbegin();
					typename Ct::reverse_iterator it2 = it;
					os << *it << "|" << *it2;
				} {
					Ct	vecfill(10, random_value);
					typename Ct::reverse_iterator it = vecfill.rbegin();
					for (size_type i = 0 ; i < vecfill.size() ; i++){ os << it[i] << " "; }
					for (size_type i = 0 ; i < vecfill.size() ; i++){ os << (it[i] = replacement) << " "; }
				}
				os << std::endl;
			}

			static void		increment_decrement(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vecfill(10, random_value);
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end() ; it++) {
						os << *it << " "; *it = replacement; }
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end() ; it++)
						os << *it << " ";
					os << std::endl;
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end() ; ++it) {
						os << *it << " "; *it = replacement; }
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end() ; ++it)
						os << *it << " ";
					os << std::endl;
				} {
					os << " DECREMENT : org_random [" << random_value << "] - replacement [" << replacement << std::endl;;
					Ct	vecfill(10, random_value);
					for (typename Ct::iterator it = vecfill.end() - 1 ; it != vecfill.begin(); --it) {
						os << *it << " "; *it = replacement; }
					for (typename Ct::iterator it = vecfill.end() - 1 ; it != vecfill.begin(); --it)
						os << *it << " ";
					os << std::endl;
				} 
				////	Reverse test
				{
					Ct	vecfill(10, random_value);
					for (typename Ct::reverse_iterator it = vecfill.rbegin() ; it != vecfill.rend() ; it++) {
						os << *it << " "; *it = replacement; }
					for (typename Ct::reverse_iterator it = vecfill.rbegin() ; it != vecfill.rend() ; it++)
						os << *it << " ";
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::reverse_iterator it = vecfill.rbegin() ; it != vecfill.rend() ; ++it) {
						os << *it << " "; *it = replacement; }
					for (typename Ct::reverse_iterator it = vecfill.rbegin() ; it != vecfill.rend() ; ++it)
						os << *it << " ";
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::reverse_iterator it = vecfill.rend() - 1 ; it != vecfill.rbegin() ; it--) {
						os << *it << " "; *it = replacement; }
					for (typename Ct::reverse_iterator it = vecfill.rend() - 1 ; it != vecfill.rbegin() ; it--)
						os << *it << " ";
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::reverse_iterator it = vecfill.rend() - 1 ; it != vecfill.rbegin() ; --it) {
						os << *it << " "; *it = replacement; }
					for (typename Ct::reverse_iterator it = vecfill.rend() - 1 ; it != vecfill.rbegin() ; --it)
						os << *it << " ";
				}
				os << std::endl;
			}

			static void		comparison(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vecfill(10, random_value);
					for (typename Ct::iterator it = vecfill.begin(), it2 = it ; it != vecfill.end() && (it == it2) ; it++, it2++) {
						os << *it << " "; *it = replacement; os << (it == it2) << " "; }
					for (typename Ct::iterator it = vecfill.begin(), it2 = it + 1 ; it != vecfill.end() && it != it2 ; it++, it2++) {
						os << *it << " " << (it != it2) << " "; }
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::iterator it = vecfill.begin() ; it < vecfill.end() ; it++)
						os << *it << " ";
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::reverse_iterator it = vecfill.rbegin() ; it < vecfill.rend() ; it++) {
						os << *it << " "; } }
				{
					Ct	vecfill(10, random_value);
					for (typename Ct::iterator it = vecfill.begin() ; it <= vecfill.end() - 1 ; it++)
						os << *it << " ";
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::reverse_iterator it = vecfill.rbegin() ; it <= vecfill.rend() - 1 ; it++) {
						os << *it << " "; }
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::iterator it = vecfill.end() - 1 ; it > vecfill.begin() ; it--)
						os << *it << " ";
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::reverse_iterator it = vecfill.rend() - 1 ; it > vecfill.rbegin() ; it--) {
						os << *it << " "; }
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::iterator it = vecfill.end() - 1 ; it >= vecfill.begin() ; it--)
						os << *it << " ";
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::reverse_iterator it = vecfill.rend() - 1 ; it >= vecfill.rbegin(); it--) {
						os << *it << " "; }
				}
				os << std::endl;
			}

			static void		arithmetic(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vecfill(20, random_value);
					typename Ct::iterator	it = vecfill.begin();
					for (size_type i = 0 ; (it + i) != vecfill.end() ; i++) {
						os << *(it + i) << " "; os << (*(it + i) = replacement); os << *(it + i) << " ";
						os << (it + i) - vecfill.begin() << " || " << typeid((it + i) - vecfill.begin()).name(); }
				} {
					Ct	vecfill(20, replacement);
					typename Ct::iterator	it = vecfill.begin();
					for (size_type i = vecfill.size() - 1 ; (i + it) >= vecfill.begin() ; i-- ) {
						os << *(i + it) << " "; os << (*(i + it) = random_value); os << *(i + it) << " "; 
						os << (it + i) - vecfill.begin() << " || " << typeid((it + i) - vecfill.begin()).name(); }
				} {
					Ct	vecfill(20, random_value);
					typename Ct::iterator	it = vecfill.end() - 1;
					for (size_type i = 0 ; i < vecfill.size() ; i++) {
						os << *(it - i) << " "; os << (*(it - i) = replacement); os << *(it - i) << " ";
						os << (it - i) - vecfill.begin() << " || " << typeid((it - i) - vecfill.begin()).name(); }
				} {
					Ct	vecfill(20, random_value);
					typename Ct::reverse_iterator	it = vecfill.rbegin();
					for (size_type i = 0 ; (it + i) != vecfill.rend() ; i++) {
						os << *(it + i) << " "; os << (*(it + i) = replacement); os << *(it + i) << " ";
						os << (it + i) - vecfill.rbegin() << " || " << typeid((it + i) - vecfill.rbegin()).name(); }
				} {
					Ct	vecfill(20, replacement);
					typename Ct::reverse_iterator	it = vecfill.rbegin();
					for (size_type i = vecfill.size() - 1 ; (i + it) >= vecfill.rbegin() ; i-- ) {
						os << *(i + it) << " "; os << (*(i + it) = random_value); os << *(i + it) << " "; 
						os << (it + i) - vecfill.rbegin() << " || " << typeid((it + i) - vecfill.rbegin()).name(); }
				} {
					Ct	vecfill(20, random_value);
					typename Ct::reverse_iterator	it = vecfill.rend() - 1;
					for (size_type i = 0 ; i < vecfill.size() ; i++) {
						os << *(it - i) << " "; os << (*(it - i) = replacement); os << *(it - i) << " ";
						os << (it - i) - vecfill.rbegin() << " || " << typeid((it - i) - vecfill.rbegin()).name(); }
				}
				os << std::endl;
			}

			static void		assignation(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vecfill(21, random_value);
					typename Ct::iterator	it = vecfill.begin();
					for (int i = 2, j = 0, result = 0 ; j < 5 ; j++, i++, result = *it + (*(it - 1) + *(it - 2))) {
						os << *(it += i) << " " ; *it = replacement ; os << *it << " i = " << i << " " << result ;}
				} {
					Ct	vecfill(21, random_value);
					typename Ct::iterator	it = vecfill.end() - 1;
					for (int i = 2, j = 0 ; j < 10 ; j++ ) {
						os << *(it -= i) << " " ; *it = replacement ; os << *it << " i = " << i << " "; }
				} {
					Ct	vecfill(21, random_value);
					typename Ct::reverse_iterator	it = vecfill.rbegin();
					for (int i = 2, j = 0, result = 0 ; j < 5 ; j++, i++, result = *it + (*(it - 1) + *(it - 2))) {
						os << *(it += i) << " " ; *it = replacement ; os << *it << " i = " << i << " " << result ;}
				} {
					Ct	vecfill(21, random_value);
					typename Ct::reverse_iterator	it = vecfill.rend() - 1;
					for (int i = 2, j = 0 ; j < 10 ; j++ ) {
						os << *(it -= i) << " " ; *it = replacement ; os << *it << " i = " << i << " "; }
				}
				os << std::endl;
			}

			static void		methods(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vec;
					vec.push_back(random_value);
					os << *vec.begin() << " ";
					for (int i = 0 ; i < 20 ; i++) {
						os << *vec.begin() << " ";
						vec.push_back(replacement);
						os << *(vec.begin() + i) << " ";
					}
				} {
					Ct vec;
					vec.push_back(random_value);
					os << *vec.begin() << " ";
					for (int i = 0 ; i < 20 ; i++) {
						vec.reserve(i);
						vec.insert(vec.begin() + i, replacement);
						os << *vec.begin() << " ";
						os << vec.end() - vec.begin() << " ";
						os << *vec.begin() + i << " ";
					}
				} {
					Ct vec;
					vec.push_back(random_value);
					os << *vec.begin() << " ";
					vec.reserve(10);
					for (int i = 0 ; i < 20 ; i++) {
						vec.insert(vec.begin() + i, replacement);
						os << *vec.begin() << " ";
						os << vec.end() - vec.begin() << " ";
						os << *vec.begin() + i << " ";
					}
				}
			}
		};
}

#endif ////////////////////////////////////////////////////////////////////////////////////////// ENDIF
