/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:05:48 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/07 18:42:22 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include "IsIntegral.hpp"
#include "EnableIf.hpp"
#include <string>
#include "Vector.hpp"

int main() {

	bool	b = true;
	std::vector<int>	vec;
	std::cout << std::boolalpha;
	std::cout << ft::is_integral< std::vector<int> >::value << std::endl;
	std::cout << ft::is_integral< bool >::value << std::endl;
	std::cout << ft::is_integral< int >::value << std::endl;
	std::cout << ft::is_integral< long int >::value << std::endl;
	std::cout << std::endl;

	std::cout << std::is_integral< std::vector<int> >::value << std::endl;
	std::cout << std::is_integral< bool >::value << std::endl;
	std::cout << std::is_integral< int >::value << std::endl;
	std::cout << std::is_integral< long int >::value << std::endl;

	std::cout << ft::enable_if< ft::is_integral<int>::value, int >::type() << std::endl;
	std::cout << std::enable_if< std::is_integral<int>::value, int >::type() << std::endl;

	std::cout << ft::enable_if< ft::is_integral<bool>::value, int >::type() << std::endl;
	std::cout << std::enable_if< std::is_integral<bool>::value, int >::type() << std::endl;

	std::vector<int>	vect(20, 100);
	std::vector<int>	vect2(20, 100);
	std::vector<int>	vect3(30, 100);
	std::vector<int>	vect4(20, 200);
	std::vector<int>	vect5(vect);

	std::cout << " TEST OPERATORS " << std::endl;
	std::cout << bool(vect < vect2) << std::endl;
	std::cout << bool(vect < vect3) << std::endl;
	std::cout << bool(vect < vect4) << std::endl;
	std::cout << bool(vect < vect5) << std::endl;

}

