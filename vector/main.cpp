/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:21:21 by guhernan          #+#    #+#             */
/*   Updated: 2022/01/11 19:49:09 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <string>

int		main(int ac, char **av) {


	std::cout << " /////////////////////////////////////////////////// " << std::endl;
	std::cout << " -------------- N = " << ac << std::endl;
	std::cout << " /////////////////////////////////////////////////// " << std::endl;


	std::vector<std::string>		args;

	std::cout << " --- size = " << args.capacity() << std::endl;

	for (int i = 1; av[i] ; i++) {
		std::cout << " /////////////////////////////////////////////////// " << std::endl;
		args.push_back(av[i]);
		std::cout << " --- I = " << i << std::endl;
		std::cout << " --- size = " << args.capacity() << std::endl;
		std::cout << " --- content = " << args[i - 1] << std::endl;
	}


}
