/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorAccessorsTests.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:14:07 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/08 12:20:11 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORACCESSORSTESTS_HPP ///////////////////////////////////////////////////////////IFNDEF
# define VECTORACCESSORSTESTS_HPP

#include <iostream>

namespace ft {

		template <class Ct, typename Os, typename type_value>

			struct UnitestAccessors {

			typedef typename Ct::size_type	size_type;

				static void				operator_bracket(Os &os, type_value random_value) {
					for (int j = 0 ; j < 100 ; j++) {
						Ct	vecfill(j, random_value);
						for (int i = 0 ; i < j ; i++) {os << vecfill[i] << " ";}
					}
					for (int j = 0 ; j < 10 ; j++) {
						const Ct	vecfill(j, random_value);
						for (int i = 0 ; i < j ; i++) {os << vecfill[i] << " ";}
					}
					os << std::endl;
				}

				static void				at(Os &os, type_value random_value) {
					for (int j = 0 ; j < 100 ; j++) {
						Ct	vecfill(j, random_value);
						for (int i = 0 ; i < j ; i++) {os << vecfill.at(i) << " ";}
					}
					for (int j = 0 ; j < 10 ; j++) {
						const Ct	vecfill(j, random_value);
						for (int i = 0 ; i < j ; i++) {os << vecfill.at(i) << " ";}
					}
					os << std::endl;
				}

				static void				front(Os &os, type_value random_value) {
					{
						Ct	vecfill(100, random_value); os << vecfill.front() << " "; 
					} {
						Ct	const vecfill(100, random_value);
						os << vecfill.front() << " ";
					}
					os << std::endl;
				}

				static void				back(Os &os, type_value random_value) {
					{
						Ct	vecfill(100, random_value); os << vecfill.back() << " "; 
					} {
						Ct	const vecfill(100, random_value);
						os << vecfill.back() << " ";
					}
					os << std::endl;
				}
			};

}

#endif ////////////////////////////////////////////////////////////////////////////////////////ENDIF
