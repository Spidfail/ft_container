/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorConstructorTests.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 22:02:42 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/08 21:54:31 by guhernan         ###   ########lyon.fr   */
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

				static void				operator_assignation(Os &os, type_value random_value) {
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

				static void				operator_comparison(Os &os, type_value random_value, type_value replacement) {
					(void)replacement;
					os << "	OPERATOR == : " << std::endl;
					{
						Ct vecfill(20, random_value);
						Ct vecfill2(10, random_value);
						Ct vecfill3(30, random_value);
  						os << bool(vecfill == vecfill2) << " " << bool(vecfill2 == vecfill) << " ";
						os << bool(vecfill == vecfill3) << " " << bool(vecfill3 == vecfill) << " ";
						os << bool(vecfill2 == vecfill3) << " " << bool(vecfill2 == vecfill3) << " ";
						os << std::endl;
					} {
						Ct vecfill(20, replacement);
						Ct vecfill2(10, replacement);
						Ct vecfill3(30, replacement);
  						os << bool(vecfill == vecfill2) << " " << bool(vecfill2 == vecfill) << " ";
						os << bool(vecfill == vecfill3) << " " << bool(vecfill3 == vecfill) << " ";
						os << bool(vecfill2 == vecfill3) << " " << bool(vecfill2 == vecfill3) << " ";
						os << std::endl;
					} {
						Ct rvecfill(20, replacement);
						Ct vecfill(20, random_value);
						Ct rvecfill2(10, replacement);
						Ct vecfill2(10, random_value);
						Ct rvecfill3(30, replacement);
						Ct vecfill3(30, random_value);
  						os << bool(vecfill == vecfill2) << " " << bool(vecfill2 == vecfill) << " ";
						os << bool(vecfill2 == rvecfill2) << " " << bool(vecfill2 == rvecfill2) << " ";
						os << bool(vecfill3 == rvecfill3) << " " << bool(vecfill3 == rvecfill3) << " ";
						os << bool(vecfill == vecfill3) << " " << bool(vecfill3 == vecfill) << " ";
						os << bool(vecfill2 == vecfill3) << " " << bool(vecfill2 == vecfill3) << " ";
						os << std::endl;
					} {
						Ct vecfill(20, random_value);
						Ct cp_vec(vecfill);
						os << bool(vecfill == cp_vec) << " " << bool(cp_vec == vecfill) << " ";
						os << std::endl;
					}

					os << "	OPERATOR != : " << std::endl;
					{
						Ct vecfill(20, random_value);
						Ct vecfill2(10, random_value);
						Ct vecfill3(30, random_value);
  						os << bool(vecfill != vecfill2) << " " << bool(vecfill2 != vecfill) << " ";
						os << bool(vecfill != vecfill3) << " " << bool(vecfill3 != vecfill) << " ";
						os << bool(vecfill2 != vecfill3) << " " << bool(vecfill2 != vecfill3) << " ";
						os << std::endl;
					} {
						Ct vecfill(20, replacement);
						Ct vecfill2(10, replacement);
						Ct vecfill3(30, replacement);
  						os << bool(vecfill != vecfill2) << " " << bool(vecfill2 != vecfill) << " ";
						os << bool(vecfill != vecfill3) << " " << bool(vecfill3 != vecfill) << " ";
						os << bool(vecfill2 != vecfill3) << " " << bool(vecfill2 != vecfill3) << " ";
						os << std::endl;
					} {
						Ct rvecfill(20, replacement);
						Ct vecfill(20, random_value);
						Ct rvecfill2(10, replacement);
						Ct vecfill2(10, random_value);
						Ct rvecfill3(30, replacement);
						Ct vecfill3(30, random_value);
  						os << bool(vecfill != vecfill2) << " " << bool(vecfill2 != vecfill) << " ";
						os << bool(vecfill2 != rvecfill2) << " " << bool(vecfill2 != rvecfill2) << " ";
						os << bool(vecfill3 != rvecfill3) << " " << bool(vecfill3 != rvecfill3) << " ";
						os << bool(vecfill != vecfill3) << " " << bool(vecfill3 != vecfill) << " ";
						os << bool(vecfill2 != vecfill3) << " " << bool(vecfill2 != vecfill3) << " ";
						os << std::endl;
					} {
						Ct vecfill(20, random_value);
						Ct cp_vec(vecfill);
						os << bool(vecfill != cp_vec) << " " << bool(cp_vec != vecfill) << " ";
						os << std::endl;
					}
					
					os << "	OPERATOR > : " << std::endl;
					{
						Ct vecfill(20, random_value);
						Ct vecfill2(10, random_value);
						Ct vecfill3(30, random_value);
  						os << bool(vecfill > vecfill2) << " " << bool(vecfill2 > vecfill) << " ";
						os << bool(vecfill > vecfill3) << " " << bool(vecfill3 > vecfill) << " ";
						os << bool(vecfill2 > vecfill3) << " " << bool(vecfill2 > vecfill3) << " ";
						os << std::endl;
					} {
						Ct vecfill(20, replacement);
						Ct vecfill2(10, replacement);
						Ct vecfill3(30, replacement);
  						os << bool(vecfill > vecfill2) << " " << bool(vecfill2 > vecfill) << " ";
						os << bool(vecfill > vecfill3) << " " << bool(vecfill3 > vecfill) << " ";
						os << bool(vecfill2 > vecfill3) << " " << bool(vecfill2 > vecfill3) << " ";
						os << std::endl;
					} {
						Ct rvecfill(20, replacement);
						Ct vecfill(20, random_value);
						Ct rvecfill2(10, replacement);
						Ct vecfill2(10, random_value);
						Ct rvecfill3(30, replacement);
						Ct vecfill3(30, random_value);
  						os << bool(vecfill > vecfill2) << " " << bool(vecfill2 > vecfill) << " ";
						os << bool(vecfill2 > rvecfill2) << " " << bool(vecfill2 > rvecfill2) << " ";
						os << bool(vecfill3 > rvecfill3) << " " << bool(vecfill3 > rvecfill3) << " ";
						os << bool(vecfill > vecfill3) << " " << bool(vecfill3 > vecfill) << " ";
						os << bool(vecfill2 > vecfill3) << " " << bool(vecfill2 > vecfill3) << " ";
						os << std::endl;
					} {
						Ct vecfill(20, random_value);
						Ct cp_vec(vecfill);
						os << bool(vecfill > cp_vec) << " " << bool(cp_vec > vecfill) << " ";
						os << std::endl;
					}

					os << "	OPERATOR < : " << std::endl;
					{
						Ct vecfill(20, random_value);
						Ct vecfill2(10, random_value);
						Ct vecfill3(30, random_value);
  						os << bool(vecfill < vecfill2) << " " << bool(vecfill2 < vecfill) << " ";
						os << bool(vecfill < vecfill3) << " " << bool(vecfill3 < vecfill) << " ";
						os << bool(vecfill2 < vecfill3) << " " << bool(vecfill2 < vecfill3) << " ";
						os << std::endl;
					} {
						Ct vecfill(20, replacement);
						Ct vecfill2(10, replacement);
						Ct vecfill3(30, replacement);
  						os << bool(vecfill < vecfill2) << " " << bool(vecfill2 < vecfill) << " ";
						os << bool(vecfill < vecfill3) << " " << bool(vecfill3 < vecfill) << " ";
						os << bool(vecfill2 < vecfill3) << " " << bool(vecfill2 < vecfill3) << " ";
						os << std::endl;
					} {
						Ct rvecfill(20, replacement);
						Ct vecfill(20, random_value);
						Ct rvecfill2(10, replacement);
						Ct vecfill2(10, random_value);
						Ct rvecfill3(30, replacement);
						Ct vecfill3(30, random_value);
  						os << bool(vecfill < vecfill2) << " " << bool(vecfill2 < vecfill) << " ";
						os << bool(vecfill2 < rvecfill2) << " " << bool(vecfill2 < rvecfill2) << " ";
						os << bool(vecfill3 < rvecfill3) << " " << bool(vecfill3 < rvecfill3) << " ";
						os << bool(vecfill < vecfill3) << " " << bool(vecfill3 < vecfill) << " ";
						os << bool(vecfill2 < vecfill3) << " " << bool(vecfill2 < vecfill3) << " ";
						os << std::endl;
					} {
						Ct vecfill(20, random_value);
						Ct cp_vec(vecfill);
						os << bool(vecfill < cp_vec) << " " << bool(cp_vec < vecfill) << " ";
						os << std::endl;
					}

					os << "	OPERATOR >= : " << std::endl;
					{
						Ct vecfill(20, random_value);
						Ct vecfill2(10, random_value);
						Ct vecfill3(30, random_value);
  						os << bool(vecfill >= vecfill2) << " " << bool(vecfill2 >= vecfill) << " ";
						os << bool(vecfill >= vecfill3) << " " << bool(vecfill3 >= vecfill) << " ";
						os << bool(vecfill2 >= vecfill3) << " " << bool(vecfill2 >= vecfill3) << " ";
						os << std::endl;
					} {
						Ct vecfill(20, replacement);
						Ct vecfill2(10, replacement);
						Ct vecfill3(30, replacement);
  						os << bool(vecfill >= vecfill2) << " " << bool(vecfill2 >= vecfill) << " ";
						os << bool(vecfill >= vecfill3) << " " << bool(vecfill3 >= vecfill) << " ";
						os << bool(vecfill2 >= vecfill3) << " " << bool(vecfill2 >= vecfill3) << " ";
						os << std::endl;
					} {
						Ct rvecfill(20, replacement);
						Ct vecfill(20, random_value);
						Ct rvecfill2(10, replacement);
						Ct vecfill2(10, random_value);
						Ct rvecfill3(30, replacement);
						Ct vecfill3(30, random_value);
  						os << bool(vecfill >= vecfill2) << " " << bool(vecfill2 >= vecfill) << " ";
						os << bool(vecfill2 >= rvecfill2) << " " << bool(vecfill2 >= rvecfill2) << " ";
						os << bool(vecfill3 >= rvecfill3) << " " << bool(vecfill3 >= rvecfill3) << " ";
						os << bool(vecfill >= vecfill3) << " " << bool(vecfill3 >= vecfill) << " ";
						os << bool(vecfill2 >= vecfill3) << " " << bool(vecfill2 >= vecfill3) << " ";
						os << std::endl;
					} {
						Ct vecfill(20, random_value);
						Ct cp_vec(vecfill);
						os << bool(vecfill >= cp_vec) << " " << bool(cp_vec >= vecfill) << " ";
						os << std::endl;
					}

					os << "	OPERATOR <= : " << std::endl;
					{
						Ct vecfill(20, random_value);
						Ct vecfill2(10, random_value);
						Ct vecfill3(30, random_value);
  						os << bool(vecfill <= vecfill2) << " " << bool(vecfill2 <= vecfill) << " ";
						os << bool(vecfill <= vecfill3) << " " << bool(vecfill3 <= vecfill) << " ";
						os << bool(vecfill2 <= vecfill3) << " " << bool(vecfill2 <= vecfill3) << " ";
						os << std::endl;
					} {
						Ct vecfill(20, replacement);
						Ct vecfill2(10, replacement);
						Ct vecfill3(30, replacement);
  						os << bool(vecfill <= vecfill2) << " " << bool(vecfill2 <= vecfill) << " ";
						os << bool(vecfill <= vecfill3) << " " << bool(vecfill3 <= vecfill) << " ";
						os << bool(vecfill2 <= vecfill3) << " " << bool(vecfill2 <= vecfill3) << " ";
						os << std::endl;
					} {
						Ct rvecfill(20, replacement);
						Ct vecfill(20, random_value);
						Ct rvecfill2(10, replacement);
						Ct vecfill2(10, random_value);
						Ct rvecfill3(30, replacement);
						Ct vecfill3(30, random_value);
  						os << bool(vecfill <= vecfill2) << " " << bool(vecfill2 <= vecfill) << " ";
						os << bool(vecfill2 <= rvecfill2) << " " << bool(vecfill2 <= rvecfill2) << " ";
						os << bool(vecfill3 <= rvecfill3) << " " << bool(vecfill3 <= rvecfill3) << " ";
						os << bool(vecfill <= vecfill3) << " " << bool(vecfill3 <= vecfill) << " ";
						os << bool(vecfill2 <= vecfill3) << " " << bool(vecfill2 <= vecfill3) << " ";
						os << std::endl;
					} {
						Ct vecfill(20, random_value);
						Ct cp_vec(vecfill);
						os << bool(vecfill <= cp_vec) << " " << bool(cp_vec <= vecfill) << " ";
						os << std::endl;
					}
				}
		};
}
