/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:17:28 by guhernan          #+#    #+#             */
/*   Updated: 2022/01/18 01:06:02 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
# define MAIN_HPP

#include "ITester.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>

#include <algorithm>
#include <vector>
#include "ft_vector.hpp"

template < typename T = int, class Allocator = std::allocator<T> >
class VectorTester : public ITester {

	public:
		typedef		typename std::vector< T, Allocator >				vector_original;
		typedef		typename ft::vector< T, Allocator >					vector_custom;

////////////////////////////////////////////////////////////////////////////////////////////////

		VectorTester() : ITester() {
		}

		VectorTester(const VectorTester &source)
			: ITester(source) {
		}

		VectorTester		&operator=(const VectorTester &source) {
			this->_test_nb = source._test_nb;
			this->_files = source._files;
			this->_files_names = source._files_names;
			this->_exec_time = source._exec_time;
			this->_turn_in_directory = source._turn_in_directory;
			return *this;
		}

		~VectorTester() {
		}

		void		init_files() {

			this->_files_names["constructor"]="_vector_constructor_results_";
			this->_files_names["accessors"]="_vector_accessors_results_";
			this->_files_names["iterators"]="_vector_iterators_results_";
			this->_files_names["capacity"]="_vector_capacity_results_";
			this->_files_names["modifiers"]="_vector_modifiers_results_";

			for (iterator_files_names it = this->_files_names.begin() ; it != this->_files_names.end() ; it++) {

				std::string		test_filename = it->second;
				test_filename.append(std::to_string(0));
				std::ifstream	test_file(this->_turn_in_directory + test_filename);

				for (int end_id = 0 ; test_file.is_open() ; ++end_id) {
					test_file.close();
					test_filename = it->second;
					test_filename.append(std::to_string(end_id));
					test_file.open(this->_turn_in_directory + test_filename);
				}
				it->second = test_filename;

				this->_files[it->first]= new std::ofstream(this->_turn_in_directory + it->second);

				this->_exec_time[it->first]=duration_type();
			}
		}
		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////CONSTRUCTORS//////////////////////////////////
		//
		void		unitest_constructor_empty() {
		}
		void		unitest_constructor_range() {
		}
		void		unitest_constructor_copy() {
		}
		void		unitest_constructor_all() { }
		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////ACCESSORS/////////////////////////////////////
		//
		int								get_test_nb() {
			return this->_test_nb;
		}

		std::ofstream					&get_file(const std::string &key) {
			return this->_files[key];
		}

		std::string						&get_file_name(const std::string &key) {
			return this->_files_names[key];
		}

		std::chrono::duration<int>		&get_exec_time(const std::string &key) {
			return this->_exec_time[key];
		}

		void							get_status() {

			iterator_files itf = this->_files.begin();
			iterator_files_names it = this->_files_names.begin();
			iterator_exec_time itt = this->_exec_time.begin();

			std::cout << " Available files :" << std::endl;
			for (; it != this->_files_names.end() ; it++, itf++) {
				std::cout << "	" << it->second;
				std::cout << "	||	IS_OPEN   " << itf->second->is_open();
				std::cout << "	||	EXEC_TIME   " << itt->second.count() << std::endl;
			}
			std::cout << " Number of tests passed : " << get_test_nb() << std::endl;
		}

		void				unitest_accessors_all() {
			std::ofstream	&os = this->_files["accessors"];

			unitest_size(os);
		}

		void				unitest_size(std::ofstream &os) {

		}
		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////CAPACITY//////////////////////////////////////
		//
		void				unitest_capacity_all() {
		}
		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////MODIFIERS/////////////////////////////////////
		//
		void				unitest_modifiers_all() {
		}


};

#endif
