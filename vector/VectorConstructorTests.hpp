/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorConstructorTests.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 22:02:42 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/07 22:11:29 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

namespace ft {

		template <class Ct, typename Os, typename T>
		struct UnitestConstructor {

			typedef	typename	Ct::size_type	size_type;
			typedef				T				type_value;

				static void				vector_fill(Os &os, type_value random_value) {
					{
						Ct	vecfill(20, random_value);
						os << vecfill.size() << std::endl;
					} {
						Ct	vecfill(0, random_value);
						os << vecfill.size() << std::endl;
					} {
						try {
							Ct	vec;
							Ct	vecfill(vec.max_size() + 1, random_value);
							os << vecfill.size() << std::endl;
						} catch (std::exception &e) { os << e.what() << std::endl; }
					} {
						try {
							Ct	vec;
							Ct	vecfill(-1, random_value);
							os << vecfill.size() << std::endl;
						} catch (std::exception &e) { os << e.what() << std::endl; }
					}
				}

				static void				vector_range(Os &os, type_value random_value) {
					{
						Ct	vectill(20, random_value);
						Ct	vecrange(vectill.begin(), vectill.end());
						for (size_type i = 0 ; i < vectill.size() ; i++) { os << vecrange[i] << " "; }
						os << std::endl;
					} {
						Ct	vecfill(20, random_value);
						Ct	vecrange(vecfill.begin(), vecfill.begin());
						os << vecrange.size() << std::endl;
					} {
						Ct	vecfill(20, random_value);
						Ct	vecrange(vecfill.begin(), vecfill.begin() + 1);
						for (size_type i = 0 ; i < vecrange.size() ; i++) { os << vecrange[i] << " "; }
						os << vecfill.size() << std::endl;
					} {
						Ct	vecfill(20, random_value);
						Ct	vecrange(vecfill.rbegin(), vecfill.rend());
						for (size_type i = 0 ; i < vecfill.size() ; i++) { os << vecrange[i] << " "; }
						os << std::endl;
					} {
						Ct	vecfill(20, random_value);
						Ct	vecrange(vecfill.rbegin(), vecfill.rbegin() + 1);
						for (size_type i = 0 ; i < vecrange.size() ; i++) { os << vecrange[i] << " "; }
						os << vecfill.size() << std::endl;
					} 
				}
				static void				operator_equal(Os &os, type_value random_value) {
					{
						Ct	vecfill(20, random_value);
						Ct	vec;
						vec = vecfill;
						for (size_type i = 0 ; i < vecfill.size() ; i++) { os << vec[i] << " "; }
						os << vecfill.size() << std::endl;
					} {
						Ct	vecfill(20, random_value);
						Ct	vec;
						vecfill = vec;
						for (size_type i = 0 ; i < vecfill.size() ; i++) { os << vecfill[i] << " "; }
						os << vecfill.size() << std::endl;
					}
				}
		};
}
