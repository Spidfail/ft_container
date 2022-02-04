/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:21:21 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/04 16:39:35 by guhernan         ###   ########.fr       */
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
	}
	catch (std::exception &e) { std::cout << e.what() << std::endl; }

	// ft::vector<int>		newvec(10, 20);
	// std::vector<int>		newvec2(10, 20);
	// ft::vector<int>::iterator	it = newvec.begin();
	// ft::vector<int>::iterator	it2 = newvec.end();
	// std::vector<int>::iterator	it3 = newvec2.begin();
	// std::vector<int>::iterator	it4 = newvec2.end();
	// std::cout << typeid(it3 - it4).name() << std::endl;
	// std::cout << *it3 << " " << ((it3 += 4) - newvec2.begin()) << std::endl;

	delete test;

	/*

	// FtVector<std::string>	test;
	// FtVector<std::string>	test2(test);

	std::cout << " /////////////////////////////////////////////////// " << std::endl;
	std::cout << " -------------- N = " << ac << std::endl;
	std::cout << " /////////////////////////////////////////////////// " << std::endl;

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	// Test constructors :
	
	{
		int limit = 100;
		//// Default:
		//
		for (int i = 0 ; i < limit ; i++) {
			std::vector<std::string>		fill(i, "manger des frites");
		}

		//// Fill :
		//
		for (int i = 0 ; i < limit ; i++) {
			std::vector<std::string>		fill(i, "manger des frites");
		}


	}





	std::vector<std::string>		args(200, "manger des frites");

	args[199] = "manger des MOULES";
	args[0] = "manger des BULOTS";

	print_state(args);

	std::vector<std::string>		testCopy(args);

	print_state(testCopy);

	std::cout << "//////////////// Test accessors " << std::endl;
	std::cout << " //////////////////        out of range :" << std::endl;



	std::cout << "//////////////// Test accessors " << std::endl;
	std::cout << " //////////////////        out of range :" << std::endl;
	try {
		std::cout << "test at : [custom] = {" << testCopy.at(200) << "}	--	[official] {" << args.at(200) << "}" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		std::cout << "test [] : [custom] = {" << testCopy[200] << "}	--	[official] {" << args[200] << "}" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << " //////////////////        Valide :" << std::endl;
	std::cout << "test at : [custom] = {" << testCopy.at(100) << "}	--	[official] {" << args.at(100) << "}" << std::endl;
	std::cout << "test [] : [custom] = {" << testCopy[100] << "}	--	[official] {" << args[100] << "}" << std::endl;


	std::cout << "test front : [custom] = {" << testCopy.front() << "}	--	[official] {" << args.front() << "}" << std::endl;
	std::cout << "test back : [custom] = {" << testCopy.back() << "}	--	[official] {" << args.back() << "}" << std::endl;
	std::cout << "test data : [custom] = {" << *testCopy.data() << "}	--	[official] {" << *args.data() << "}" << std::endl;




	std::cout << "//////////////// Test capacity " << std::endl;
	std::cout << " //////////////////        Exception :" << std::endl;


	std::cout << " //////////////////        Valide :" << std::endl;

	std::cout << "test empty : [custom] = {" << testCopy.empty() << "}	--	[official] {" << args.empty() << "}" << std::endl;
	std::cout << "test size : [custom] = {" << testCopy.size() << "}	--	[official] {" << args.size() << "}" << std::endl;

	args.reserve(300);
	testCopy.reserve(300);
	std::cout << "test reserve : [custom] = {" << testCopy.size() << "}	--	[official] {" << args.size() << "}" << std::endl;
	std::cout << "test reserve : [custom] = {" << testCopy.capacity() << "}	--	[official] {" << args.capacity() << "}" << std::endl;

	std::cout << "test max_size : [custom] = {" << testCopy.max_size() << "}	--	[official] {" << args.max_size() << "}" << std::endl;

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
//
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
//
	// std::cout << (testAlloc + 3) - testAlloc << std::endl;
//
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

*/


}
