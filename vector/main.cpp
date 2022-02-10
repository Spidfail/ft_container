/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:21:21 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/09 22:14:55 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <algorithm>
#include "Vector.hpp"
#include "VectorTester.hpp"
#include "ITester.hpp"
#include "IteratorVector.hpp"
#include "IsIntegral.hpp"
#include <typeinfo>

int		main(int ac, char **av) {

	(void)av;
	(void)ac;

	ft::ITester	*test = new VectorTester<int>;
	test->init();
	test->get_status();
	try {
		test->launch_capacity();
		test->launch_accessors();
		test->launch_modifiers();
		test->launch_iterators();
		test->launch_constructor();
	}
	catch (std::exception &e) { std::cout << e.what() << std::endl; }

	delete test;
}
