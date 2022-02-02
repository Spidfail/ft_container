/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:05:48 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/02 18:38:36 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include "IsIntegral.hpp"
#include "EnableIf.hpp"
#include <string>

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

	std::cout << ft::enable_if< ft::is_integral<int>::value , int >::type() << std::endl;

}

