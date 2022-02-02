/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IsIntegral.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:31:51 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/02 17:49:56 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

#include <type_traits>

namespace ft {

	template <class T, T v>
		struct integral_constant {
			static constexpr T value = v;
			typedef T value_type;
			typedef integral_constant<T,v> type;
			constexpr operator T() { return v; }
		};

	// equivalent to std::true_type and std::false_type
	typedef	integral_constant<bool, true>	true_type;
	typedef	integral_constant<bool, false>	false_type;

	// default case : type is not integral
	template <class T> struct is_integral : public false_type {};

	// specialized template : type is integral
	template <> struct is_integral<bool> : public true_type {};
	template <> struct is_integral<char> : public true_type {};
	template <> struct is_integral<char16_t> : public true_type {};
	template <> struct is_integral<char32_t> : public true_type {};
	template <> struct is_integral<wchar_t> : public true_type {};
	template <> struct is_integral<signed char> : public true_type {};
	template <> struct is_integral<short int> : public true_type {};
	template <> struct is_integral<int> : public true_type {};
	template <> struct is_integral<long int> : public true_type {};
	template <> struct is_integral<long long int> : public true_type {};
	template <> struct is_integral<unsigned char> : public true_type {};
	template <> struct is_integral<unsigned short int> : public true_type {};
	template <> struct is_integral<unsigned int> : public true_type {};
	template <> struct is_integral<unsigned long int> : public true_type {};
	template <> struct is_integral<unsigned long long int> : public true_type {};
}

#endif
