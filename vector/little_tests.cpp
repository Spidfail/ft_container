/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:05:48 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/01 21:09:14 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include "IsIntegral.hpp"
#include <string>

int main() {

	bool	b = true;
	std::vector<int>	vec;
	std::cout << std::boolalpha;
	std::cout << ft::is_integral< std::vector<int> >::value << std::endl;

}

