/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:05:48 by guhernan          #+#    #+#             */
/*   Updated: 2022/01/26 14:31:56 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <algorithm>
#include <iostream>

int main() {

	std::vector<int>	test(10, 150);
	int					store[4] = {1, 2, 3, 4};

	std::vector<int>::iterator	it = test.begin();
	std::vector<int>::iterator	it2 = test.begin();
	std::vector<int>::iterator	it3(store);

	std::advance(it, 5);

	test.insert(it, 200);

	it = test.begin();
	it2 = test.begin();


	it.base();

	std::cout << *(it + 5) << std::endl;
	std::cout << *(5 + it) << std::endl;
	std::cout << ((it + 5) - it) << std::endl;


}

