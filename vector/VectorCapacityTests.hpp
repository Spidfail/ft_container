/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorCapacityTests.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 22:12:50 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/08 12:21:26 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORCAPACITYTESTS_HPP //////////////////////////////////////////////////////////IFNDEF
# define VECTORCAPACITYTESTS_HPP

#include <iostream>

namespace ft {

		template <class Ct, typename Os, typename T>
		struct UnitestCapacity {

			typedef	typename	Ct::size_type	size_type;
			typedef				T				type_value;

				static void				empty(Os &os, type_value random_value) {
					{
						Ct	vec;
						os << vec.empty() << " ";
						vec.push_back(random_value);
						os << vec.empty() << " ";
					} {
						Ct	vecfill(20, random_value);
						os << vecfill.empty() << " ";
					}
				}

				static void				size(Os &os, type_value random_value) {
					{
						Ct	vec;
						os << vec.size() << " ";
					} {
						Ct	vecfill(20, random_value);
						os << vecfill.size() << " ";
					}
					os << std::endl;
				}

				static void				reserve(Os &os, type_value random_value) {
					(void) random_value;
					{
						Ct	vec;
						vec.reserve(100);
						os << vec.capacity() << " " ;
					} {
						Ct	vecfill(20, random_value);
						vecfill.reserve(100);
						os << vecfill.capacity() << " " ;
					} {
						Ct	vecfill(200, random_value);
						vecfill.reserve(100);
						os << vecfill.capacity() << " " ;
					} try {
						Ct	vecfill(20, random_value);
						vecfill.reserve(vecfill.max_size() + 1);
						os << vecfill.capacity() << " WRONG : AN EXCEPTION MUST BE THROWN " ;
					} catch (std::exception &e) {
						os << e.what() << " ";
					}
					os << std::endl;
				}

				static void				max_size(Os &os) {
					Ct	vec;
					os << vec.max_size() << " ";
					os << std::endl;
				}

				static void				capacity(Os &os, type_value random_value) {
					{
						Ct	vec;
						os << vec.capacity() << " ";
					} {
						Ct	vecfill(20, random_value);
						os << vecfill.capacity() << " ";
					}
				}
		};

}

#endif //////////////////////////////////////////////////////////////////////////////////////////ENDIF
