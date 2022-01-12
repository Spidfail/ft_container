/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:21:21 by guhernan          #+#    #+#             */
/*   Updated: 2022/01/12 19:37:06 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <algorithm>
#include "ft_vector.hpp"

void	print_state(std::vector<std::string> const &target) {

	std::cout << " --- capacity = " << target.capacity() << std::endl;
	std::cout << " --- size = " << target.size() << std::endl;
	std::cout << " --- max size = " << target.max_size() << std::endl;

}

int		main(int ac, char **av) {


	// FtVector<std::string>	test;
	// FtVector<std::string>	test2(test);

	std::cout << " /////////////////////////////////////////////////// " << std::endl;
	std::cout << " -------------- N = " << ac << std::endl;
	std::cout << " /////////////////////////////////////////////////// " << std::endl;


	std::vector<std::string>		args(200, "Manger des frites");

	print_state(args);

	for (int i = 1; av[i] ; i++) {
		std::cout << " /////////////////////////////////////////////////// " << std::endl;
		args.push_back(av[i]);
		print_state(args);
	}

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	// std::allocator< std::string >		alloc;
//
	// std::string		*testAlloc = alloc.allocate(5);
//
	// testAlloc[0].assign("Manger des frites");
	// testAlloc[1].assign("Manger des moules");
	// testAlloc[2].assign("Manger des coquillettes");
	// testAlloc[3].assign("Manger des spaghettis");
//
	// for (int i = 0 ; !testAlloc[i].empty() ; i++) {
		// std::cout << testAlloc[i] << std::endl;
	// }

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////




}
