/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorTester.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:17:28 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/07 00:32:20 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
# define MAIN_HPP

#include "ITester.hpp"

#include <iostream>
#include <filesystem>

#include <algorithm>
#include <vector>

#include "ft_random.hpp"
#include "Vector.hpp"

#include <cstdlib>
#include <time.h>


template < typename T = int, class Allocator = std::allocator<T> >
class VectorTester : public ft::ITester {

	public:
		typedef		typename std::vector< T, Allocator >		vector_original;
		typedef		typename ft::vector< T, Allocator >			vector_custom;
		typedef		typename ft::ITester::Folder				type_folder;
		typedef		T											type_value;

	protected:
		void		_init_files(std::string container_name = "vector", std::string dir_path = "./gunner_results/") {
			this->_folder_std = new type_folder(container_name, "std", dir_path + "details_std/");
			this->_folder_ft = new type_folder(container_name, "ft", dir_path + "details_ft/");
			this->_folder_std->_init_folder();
			this->_folder_ft->_init_folder();
		}

		void		_init_exec_time() {
			for (ft::ITester::iterator_files_names	it = _folder_ft->begin_files_names() ;
					it != _folder_ft->end_files_names(); it++) {
				std::pair< std::string, type_duration >		pair_exec_time(it->first, type_duration());
				this->_exec_time.insert(pair_exec_time);
			}
		}


	public:
		/////////////////////////////////////////////////////////////////////////////////////
		VectorTester() : ft::ITester() {
			std::cout << std::boolalpha;
		}

		VectorTester(const VectorTester &source)
			: ft::ITester(source) {
		}

		VectorTester		&operator=(const VectorTester &source) {
			this->_test_nb = source._test_nb;
			this->_files_org = source._files_org;
			this->_files_cust = source._files_cust;
			this->_files_names_org = source._files_names_org;
			this->_files_names_cust = source._files_names_cust;
			this->_exec_time = source._exec_time;
			this->_turn_in_directory = source._turn_in_directory;
			return *this;
		}

		virtual ~VectorTester() {
			delete this->_folder_std;
			delete this->_folder_ft;
		}

		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////UTILS/////////////////////////////////////////
		//
		template <typename Os, class Ct>
		static void		print_state(Os &os, Ct vector) {
			os << vector.size() << "|" << vector.capacity();
		}

		template <typename Os, class Ct>
		static void		print_content(Os &os, Ct vector) {
			for (size_type i = 0 ; i < vector.size() ; i++) {
				os << vector[i] << " ";
			}
		}
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////INITIALISATION////////////////////////////////
		//
		void		init() {
			_init_files();
			_init_exec_time();
		}
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////GETTERS///////////////////////////////////////
		//
		int									get_test_nb() { return this->_test_nb; }

		type_folder							&get_folder_std() { return *this->_folder_std; }

		type_folder							&get_folder_ft() { return *this->_folder_ft; }

		type_exec_time						&get_exec_time() { return this->_exec_time; }

		type_duration						&get_exec_time(const std::string &key) { return this->_exec_time[key]; }

		void								get_status() {
			{
				ft::ITester::iterator_files_names	it = get_folder_std().begin_files_names();
				ft::ITester::iterator_files			it2 = get_folder_std().begin_files();
				ft::ITester::iterator_exec_time		it3 = get_exec_time().begin();


				while (it != get_folder_std().end_files_names() && it2 != get_folder_std().end_files()
						&& it3 != get_exec_time().end()) {
					std::cout << "	" << it->second;
					std::cout << "	||	IS_OPEN   " << it2->second->is_open();
					std::cout << "	||	EXEC_TIME   " << it3->second.count() << std::endl;
					++it;
				}
				std::cout << " Number of tests passed : " << _test_nb << std::endl;
			}

			{
				ft::ITester::iterator_files_names	it = get_folder_ft().begin_files_names();
				ft::ITester::iterator_files			it2 = get_folder_ft().begin_files();
				ft::ITester::iterator_exec_time		it3 = get_exec_time().begin();

				while (it != get_folder_ft().end_files_names() && it2 != get_folder_ft().end_files()
						&& it3 != get_exec_time().end()) {
					std::cout << "	" << it->second;
					std::cout << "	||	IS_OPEN   " << it2->second->is_open();
					std::cout << "	||	EXEC_TIME   " << it3->second.count() << std::endl;
					++it;
				}
				std::cout << " Number of tests passed : " << _test_nb << std::endl;
			}
		}
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////TESTS///////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////CONSTRUCTORS//////////////////////////////////
		//
		template <class Ct, typename Os>
		struct UnitestConstructor {

			typedef typename Ct::size_type	size_type;

				static void				vector_fill(Os &os, type_value random_value) {
					{
						Ct	vecfill(20, random_value);
						os << vecfill.size() << std::endl;
					} {
						Ct	vecfill(0, random_value);
						os << vecfill.size() << std::endl;
					} {
						try {
							Ct	vec;
							Ct	vecfill(vec.max_size() + 1, random_value);
							os << vecfill.size() << std::endl;
						} catch (std::exception &e) { os << e.what() << std::endl; }
					} {
						try {
							Ct	vec;
							Ct	vecfill(-1, random_value);
							os << vecfill.size() << std::endl;
						} catch (std::exception &e) { os << e.what() << std::endl; }
					}
				}

				static void				vector_range(Os &os, type_value random_value) {
					{
						Ct	vectill(20, random_value);
						Ct	vecrange(vectill.begin(), vectill.end());
						for (size_type i = 0 ; i < vectill.size() ; i++) { os << vecrange[i] << " "; }
						os << std::endl;
					} {
						Ct	vecfill(20, random_value);
						Ct	vecrange(vecfill.begin(), vecfill.begin());
						os << vecrange.size() << std::endl;
					} {
						Ct	vecfill(20, random_value);
						Ct	vecrange(vecfill.begin(), vecfill.begin() + 1);
						for (size_type i = 0 ; i < vecrange.size() ; i++) { os << vecrange[i] << " "; }
						os << vecfill.size() << std::endl;
					} {
						Ct	vecfill(20, random_value);
						Ct	vecrange(vecfill.rbegin(), vecfill.rend());
						for (size_type i = 0 ; i < vecfill.size() ; i++) { os << vecrange[i] << " "; }
						os << std::endl;
					} {
						Ct	vecfill(20, random_value);
						Ct	vecrange(vecfill.rbegin(), vecfill.rbegin() + 1);
						for (size_type i = 0 ; i < vecrange.size() ; i++) { os << vecrange[i] << " "; }
						os << vecfill.size() << std::endl;
					} 
				}
				static void				operator_equal(Os &os, type_value random_value) {
					{
						Ct	vecfill(20, random_value);
						Ct	vec;
						vec = vecfill;
						for (size_type i = 0 ; i < vecfill.size() ; i++) { os << vec[i] << " "; }
						os << vecfill.size() << std::endl;
					} {
						Ct	vecfill(20, random_value);
						Ct	vec;
						vecfill = vec;
						for (size_type i = 0 ; i < vecfill.size() ; i++) { os << vecfill[i] << " "; }
						os << vecfill.size() << std::endl;
					}
				}
		};

		void		launch_constructor() {
			typedef		UnitestConstructor<vector_custom, std::ofstream>		constructor_custom;
			typedef		UnitestConstructor<vector_original, std::ofstream>		constructor_original;

			ft::Random<type_value>	random;
			type_value		random_value = random.generate(type_value());
			type_file		os_std = this->get_folder_std().get_file("constructor");
			type_file		os_ft = this->get_folder_ft().get_file("constructor");

			constructor_original::vector_fill(*os_std, random_value);
			constructor_custom::vector_fill(*os_ft, random_value);
			constructor_original::vector_range(*os_std, random_value);
			constructor_custom::vector_range(*os_ft, random_value);
			constructor_original::operator_equal(*os_std, random_value);
			constructor_custom::operator_equal(*os_ft, random_value);
		}

		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////MEMBERS///////////////////////////////////////
		//

		
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////CAPACITY//////////////////////////////////////
		//
		template <class Ct, typename Os>
		struct UnitestCapacity {

			typedef typename Ct::size_type	size_type;

				static void				empty(Os &os, type_value random_value) {
					{
						Ct	vec;
						os << vec.empty() << " ";
						vec.push_back(random_value);
						os << vec.empty() << " ";
					} {
						Ct	vecfill(20, random_value);
						os << vecfill.empty() << " ";
					}
				}

				static void				size(Os &os, type_value random_value) {
					{
						Ct	vec;
						os << vec.size() << " ";
					} {
						Ct	vecfill(20, random_value);
						os << vecfill.size() << " ";
					}
					os << std::endl;
				}

				static void				reserve(Os &os, type_value random_value) {
					(void) random_value;
					{
						Ct	vec;
						vec.reserve(100);
						os << vec.capacity() << " " ;
					} {
						Ct	vecfill(20, random_value);
						vecfill.reserve(100);
						os << vecfill.capacity() << " " ;
					} {
						Ct	vecfill(200, random_value);
						vecfill.reserve(100);
						os << vecfill.capacity() << " " ;
					} try {
						Ct	vecfill(20, random_value);
						vecfill.reserve(vecfill.max_size() + 1);
						os << vecfill.capacity() << " WRONG : AN EXCEPTION MUST BE THROWN " ;
					} catch (std::exception &e) {
						os << e.what() << " ";
					}
					os << std::endl;
				}

				static void				max_size(Os &os) {
					Ct	vec;
					os << vec.max_size() << " ";
					os << std::endl;
				}

				static void				capacity(Os &os, type_value random_value) {
					{
						Ct	vec;
						os << vec.capacity() << " ";
					} {
						Ct	vecfill(20, random_value);
						os << vecfill.capacity() << " ";
					}
				}
		};


		void				launch_capacity() {

			typedef		UnitestCapacity<vector_custom, std::ofstream>		capacity_custom;
			typedef		UnitestCapacity<vector_original, std::ofstream>		capacity_original;

			ft::Random<type_value>	random;
			type_value		random_value = random.generate(type_value());
			type_file		os_std = this->get_folder_std().get_file("capacity");
			type_file		os_ft = this->get_folder_ft().get_file("capacity");

			capacity_original::max_size(*os_std);
			capacity_custom::max_size(*os_ft);
			capacity_original::size(*os_std, random_value);
			capacity_custom::size(*os_ft, random_value);
			capacity_original::empty(*os_std, random_value);
			capacity_custom::empty(*os_ft, random_value);
			capacity_original::capacity(*os_std, random_value);
			capacity_custom::capacity(*os_ft, random_value);
			capacity_original::reserve(*os_std, random_value);
			capacity_custom::reserve(*os_ft, random_value);
		}

		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////ACCESSORS/////////////////////////////////////
		//
		template <class Ct, typename Os>


			struct UnitestAccessors {

			typedef typename Ct::size_type	size_type;

				static void				operator_bracket(Os &os, type_value random_value) {
					for (int j = 0 ; j < 100 ; j++) {
						Ct	vecfill(j, random_value);
						for (int i = 0 ; i < j ; i++) {os << vecfill[i] << " ";}
					}
					for (int j = 0 ; j < 10 ; j++) {
						const Ct	vecfill(j, random_value);
						for (int i = 0 ; i < j ; i++) {os << vecfill[i] << " ";}
					}
					os << std::endl;
				}

				static void				at(Os &os, type_value random_value) {
					for (int j = 0 ; j < 100 ; j++) {
						Ct	vecfill(j, random_value);
						for (int i = 0 ; i < j ; i++) {os << vecfill.at(i) << " ";}
					}
					for (int j = 0 ; j < 10 ; j++) {
						const Ct	vecfill(j, random_value);
						for (int i = 0 ; i < j ; i++) {os << vecfill.at(i) << " ";}
					}
					os << std::endl;
				}

				static void				front(Os &os, type_value random_value) {
					{
						Ct	vecfill(100, random_value); os << vecfill.front() << " "; 
					} {
						Ct	const vecfill(100, random_value);
						os << vecfill.front() << " ";
					}
					os << std::endl;
				}

				static void				back(Os &os, type_value random_value) {
					{
						Ct	vecfill(100, random_value); os << vecfill.back() << " "; 
					} {
						Ct	const vecfill(100, random_value);
						os << vecfill.back() << " ";
					}
					os << std::endl;
				}
			};

		void				launch_accessors() {

			ft::Random<type_value>	random;
			type_value		random_value = random.generate(type_value());
			typedef		UnitestAccessors<vector_custom, std::ofstream>		accessors_custom;
			typedef		UnitestAccessors<vector_original, std::ofstream>		accessors_original;

			type_file		os_std = get_folder_std().get_file("accessors");
			type_file		os_ft = get_folder_ft().get_file("accessors");

			accessors_original::operator_bracket(*os_std, random_value);
			accessors_custom::operator_bracket(*os_ft, random_value);
			accessors_original::at(*os_std, random_value);
			accessors_custom::at(*os_ft, random_value);
			accessors_original::front(*os_std, random_value);
			accessors_custom::front(*os_ft, random_value);
		}


		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////MODIFIERS/////////////////////////////////////
		//

		template <class Ct, typename Os>
		struct UnitestModifiers {

			typedef typename Ct::size_type	size_type;

			static void					assign(Os &os, type_value random_value, type_value replacement) {
				os << "ASSIGN" << std::endl;
				{
					Ct	vec;
					vec.assign(20, random_value);
					for (size_type i = 0 ; i < vec.size() ; i++) { os << vec[i] << " "; }
					vec.assign(50, replacement);
					for (size_type i = 0 ; i < vec.size() ; i++) { os << vec[i] << " "; }
					vec.assign(10, random_value);
					for (size_type i = 0 ; i < vec.size() ; i++) { os << vec[i] << " "; }
				os << std::endl;
				} {
					Ct	vecfill(10, random_value);
					vecfill.assign(10, random_value);
					vecfill.assign(20, replacement);
					for (size_type i = 0 ; i < vecfill.size() ; i++) { os << vecfill[i] << " "; }
				} {
					Ct	vecfill(20, random_value);
					vecfill.assign(20, replacement);
					vecfill.assign(30, replacement);
					for (size_type i = 0 ; i < vecfill.size() ; i++) { os << vecfill[i] << " "; }
				os << std::endl;
				} { // range form
					Ct	vec;
					Ct	vecfill(20, random_value);
					for (size_type i = 2 ; i < vecfill.size() ; i++) {
						vec.assign(vecfill.begin(), vecfill.begin() + i);
						os << *(vecfill.begin() + i) << " "; }

					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end(); it++) { os << *it << " "; }
				os << std::endl;
				} {
					Ct	vec;
					Ct	vecfill(20, replacement);
					for (size_type i = vecfill.size() - 1 ; i > 0 ; i--) {
						vec.assign(vecfill.begin(), vecfill.begin() + i);
						os << *(vecfill.begin() + i) << " "; }
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end(); it++) { os << *it << " "; }
				os << std::endl;
				} {
					Ct	vecfill(20, random_value);
					vecfill.assign(vecfill.begin(), vecfill.end());
					for (typename Ct::iterator it = vecfill.begin() ;
							it != vecfill.end(); it++)
						os << *it << " ";
				}
				os << std::endl;
			}

			static void					clear(Os &os, type_value random_value, type_value replacement) {
				os << "CLEAR" << std::endl;
				Ct	vecfill(10, random_value);
				os << vecfill.capacity() << " ";
				os << vecfill.size() << " ";
				vecfill.clear();
				os << vecfill.capacity() << " ";
				os << vecfill.size() << " ";
				(void)replacement;
				for (size_type i = 0 ; i < vecfill.capacity(); i++) {
					vecfill.push_back(replacement);
				}
				os << vecfill.capacity() << " ";
				os << vecfill.size() << " ";
				os << std::endl;
			}

			static void					insert(Os &os, type_value random_value, type_value replacement) {
				{
					os << "INSERT" << std::endl;
					Ct vecfill(10, random_value);
					vecfill.reserve(20);
					typename Ct::iterator	it_end = vecfill.end();
					for (typename Ct::iterator it = vecfill.begin() ; it != it_end ; it++) {
						typename Ct::iterator it_tmp = vecfill.insert(it, replacement);
						os << *it_tmp << " " << (vecfill.end() - it_tmp) << " "; }
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end() ; it++)
						os << *it << " ";
					os << std::endl;
				} {
					Ct vecfill(10, random_value);
					typename Ct::iterator	it_pos = vecfill.begin();
					vecfill.insert(it_pos, 10, replacement);
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end() ; it++)
						os << *it << " ";
					os << std::endl;
				} {
					Ct vecfill(10, random_value);
					typename Ct::iterator	it_pos = vecfill.begin() + 5;
					vecfill.insert(it_pos, 5, replacement);
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end() ; it++)
						os << *it << " ";
					os << std::endl;
				} {
					Ct vecfill(10, random_value);
					typename Ct::iterator	it_pos = vecfill.begin() + 10;
					vecfill.insert(it_pos, 10, replacement);
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end() ; it++)
						os << *it << " ";
					os << std::endl;
				} {
					Ct vecfill(10, random_value);
					typename Ct::iterator	it_pos = vecfill.begin() + 5;
					vecfill.insert(it_pos, 5, replacement);
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end() ; it++)
						os << *it << " ";
					os << std::endl;
				} {
					Ct vecfill(3, random_value);
					Ct rvecfill(3, replacement);
					typename Ct::iterator	fst_it = rvecfill.begin();
					typename Ct::iterator	end_it = rvecfill.begin();
					typename Ct::iterator	it_pos = vecfill.begin();
					for ( size_type i = vecfill.size(), j = 0 ; i && j < 4 ; --i, ++j ) {
						vecfill.insert(it_pos, fst_it, end_it + j);
						it_pos = vecfill.end() - i;
					}
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end() ; it++)
						os << *it << " ";
					os << std::endl;
				} {
					Ct vecfill(10, random_value);
					Ct rvecfill(10, replacement);
					typename Ct::iterator	fst_it = rvecfill.begin();
					typename Ct::iterator	end_it = rvecfill.end() - 5;
					typename Ct::iterator	it_pos = vecfill.begin() + 5;
					vecfill.insert(it_pos, fst_it, end_it);
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end() ; it++)
						os << *it << " ";
					os << std::endl;
				} {
					Ct vecfill(10, random_value);
					Ct rvecfill(10, replacement);
					typename Ct::iterator	fst_it = rvecfill.begin();
					typename Ct::iterator	end_it = rvecfill.end();
					typename Ct::iterator	it_pos = vecfill.end();
					vecfill.insert(it_pos, fst_it, end_it);
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end() ; it++)
						os << *it << " ";
					os << std::endl;
				}
				os << std::endl;
			}

			static void					push_back(Os &os, type_value random_value, type_value replacement) {
				size_type	max_size;
				{
					Ct	vec;
					max_size = vec.max_size();
					for (size_type i = 0 ; i < 20 ; i++) {
						if (i % 2 == 0)
							vec.push_back(random_value);
						else
							vec.push_back(replacement);
						os << vec[i] << "|" << vec.capacity() << "|" << vec.size() << " ";
					}
					vec.clear();
					for (size_type i = 0 ; i < 30 ; i++) {
						vec.push_back(replacement);
						os << vec.capacity() << "|" << vec.size() << " ";
					}
				}
				os << std::endl;
			}

			static void					pop_back(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vecfill(10, random_value);
					for ( ; vecfill.size() ; vecfill.pop_back() ) {
						os << vecfill.size() << " ";
						for (typename Ct::size_type i = 0 ; i < vecfill.size() ; i++) { os << vecfill[i] << " "; }
					}
					os << std::endl;
					for ( ; vecfill.size() < 20 ; vecfill.push_back(replacement) ) { os << vecfill.size() << " "; }
					for (typename Ct::size_type j = 0 ; j < vecfill.size() ; j++) { os << vecfill[j] << " "; }
					for ( ; vecfill.size() ; vecfill.pop_back() ) {
						os << vecfill.size() << " ";
						for (typename Ct::size_type i = 0 ; i < vecfill.size() ; i++) { os << vecfill[i] << " "; }
					}
				}
				os << std::endl;
			}

			static void					resize(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vecfill(10, random_value);
					vecfill.resize(10);
					for (size_type i = 0 ; i < vecfill.size() ; ++i)
						os << vecfill[i] << " ";
					vecfill.resize(20);
					os << vecfill.size() << " ";
					for (size_type i = 0 ; i < vecfill.size() ; ++i)
						os << vecfill[i] << " ";
					vecfill.resize(20);
					os << vecfill.size() << " ";
					for (size_type i = 0 ; i < vecfill.size() ; ++i)
						os << vecfill[i] << " ";
					vecfill.resize(30, replacement);
					os << vecfill.size() << " ";
					for (size_type i = 0 ; i < vecfill.size() ; ++i)
						os << vecfill[i] << " ";
					vecfill.resize(30);
					os << vecfill.size() << " ";
					for (size_type i = 0 ; i < vecfill.size() ; ++i)
						os << vecfill[i] << " ";
					vecfill.resize(20);
					os << vecfill.size() << " ";
					for (size_type i = 0 ; i < vecfill.size() ; ++i)
						os << vecfill[i] << " ";
					vecfill.resize(20);
					os << vecfill.size() << " ";
					for (size_type i = 0 ; i < vecfill.size() ; ++i)
						os << vecfill[i] << " ";
					vecfill.resize(0);
					os << vecfill.size() << " ";
					os << std::endl;
				}
			}

			static void					swap(Os &os, type_value random_value, type_value replacement) {
				{
					Ct vecfill(10, random_value);
					Ct vecfill_other(10, replacement);
					vecfill.swap(vecfill_other);
					print_content(os, vecfill);
					std::swap(vecfill_other, vecfill);
					print_content(os, vecfill);
				} {
					Ct vecfill(10, random_value);
					Ct vecfill_other(20, replacement);
					vecfill.swap(vecfill_other);
					print_content(os, vecfill);
					std::swap(vecfill_other, vecfill);
					print_content(os, vecfill);
				} {
					Ct vecfill(30, random_value);
					Ct vecfill_other(20, replacement);
					vecfill.swap(vecfill_other);
					print_content(os, vecfill);
					std::swap(vecfill_other, vecfill);
					print_content(os, vecfill);
				}
				os << std::endl;
			}

			static void					erase(Os &os, type_value random_value, type_value replacement) {
				os << " ERASE " << std::endl;
				{
					Ct	vecfill(20, random_value);
					int i = 0;
					while (i < 20) {
						vecfill.erase(vecfill.begin());
						os << vecfill.size() << " ";
						++i;
					}
					os << std::endl;
				} {
					Ct	vecfill(20, random_value);
					size_type	pos_array[3] = {0, 5, 17};
					for ( int i = 0 ; i < 3 ; ++i ) {
						vecfill.erase(vecfill.begin() + pos_array[i]);
						os << vecfill.size() << " ";
					}
					for ( size_type i = 0 ; i < vecfill.size() ; ++i )
						os << *(vecfill.begin() + i) << " ";
					os << std::endl;
				} {
					Ct	vecfill(20, random_value);
					int i = 0;
					while (i < 20) {
						vecfill.erase(vecfill.end() - 1);
						os << vecfill.size() << " ";
						++i;
					}
					os << std::endl;
				} {
					os << "random_value : " <<  random_value << " replacement : " << replacement << std::endl;
					Ct	vecfill(10, random_value);
					vecfill.insert(vecfill.end(), 10, replacement);
					for ( size_type i = 0 ; i < vecfill.size() ; ++i )
						os << *(vecfill.begin() + i) << " ";
					os << std::endl;
					vecfill.erase(vecfill.begin(), vecfill.begin() + 10);
					os << vecfill.size() << " ";
					for ( size_type i = 0 ; i < vecfill.size() ; ++i )
						os << *(vecfill.begin() + i) << " ";
					os << std::endl;
				} {
					os << "random_value : " <<  random_value << " replacement : " << replacement << std::endl;
					Ct	vecfill(10, random_value);
					vecfill.insert(vecfill.end(), 10, replacement);
					for ( size_type i = 0 ; i < vecfill.size() ; ++i )
						os << *(vecfill.begin() + i) << " ";
					os << std::endl;
					vecfill.erase(vecfill.begin() + 10, vecfill.end());
					os << vecfill.size() << " ";
					for ( size_type i = 0 ; i < vecfill.size() ; ++i )
						os << *(vecfill.begin() + i) << " ";
					os << std::endl;
				} {
					os << "random_value : " <<  random_value << " replacement : " << replacement << std::endl;
					Ct	vecfill(10, random_value);
					vecfill.insert(vecfill.end(), 10, replacement);
					for ( size_type i = 0 ; i < vecfill.size() ; ++i )
						os << *(vecfill.begin() + i) << " ";
					os << std::endl;
					vecfill.erase(vecfill.begin() + 5, vecfill.end() - 5);
					os << vecfill.size() << " ";
					for ( size_type i = 0 ; i < vecfill.size() ; ++i )
						os << *(vecfill.begin() + i) << " ";
					os << std::endl;
				}
			}

		};

		void				launch_modifiers() {
			ft::Random<type_value>	random;
			type_value		random_value = random.generate(type_value());
			type_value		replacement = random.generate(type_value()) / 2;
			typedef		UnitestModifiers<vector_custom, std::ofstream>		modifiers_custom;
			typedef		UnitestModifiers<vector_original, std::ofstream>		modifiers_original;

			type_file		os_std = get_folder_std().get_file("modifiers");
			type_file		os_ft = get_folder_ft().get_file("modifiers");
			modifiers_original::assign(*os_std, random_value, replacement);
			modifiers_custom::assign(*os_ft, random_value, replacement);
			modifiers_original::clear(*os_std, random_value, replacement);
			modifiers_custom::clear(*os_ft, random_value, replacement);
			modifiers_original::insert(*os_std, random_value, replacement);
			modifiers_custom::insert(*os_ft, random_value, replacement);
			modifiers_original::push_back(*os_std, random_value, replacement);
			modifiers_custom::push_back(*os_ft, random_value, replacement);
			modifiers_original::pop_back(*os_std, random_value, replacement);
			modifiers_custom::pop_back(*os_ft, random_value, replacement);
			modifiers_original::swap(*os_std, random_value, replacement);
			modifiers_custom::swap(*os_ft, random_value, replacement);
			modifiers_original::erase(*os_std, random_value, replacement);
			modifiers_custom::erase(*os_ft, random_value, replacement);
			modifiers_original::resize(*os_std, random_value, replacement);
			modifiers_custom::resize(*os_ft, random_value, replacement);
		}

		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////ITERATORS/////////////////////////////////////
		//
		template <class Ct, typename Os>
		struct UnitestIterators {

			typedef typename Ct::size_type	size_type;

			static void		constructors(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vecfill(10, random_value);
					typename Ct::iterator it;
					it = vecfill.begin();

					Ct	vecfill2(20, replacement);
					vecfill = vecfill2;
					typename Ct::iterator it2 = vecfill.begin();

					os << std::boolalpha << (it == it2) << " ";
				}
				os << std::endl;
			}

			static void		accessors(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vecfill(1, random_value);
					vecfill.push_back(replacement);
					typename Ct::iterator it = vecfill.begin();
					typename Ct::iterator it2 = it;
					os << *it << "|" << *it2;
				} {
					Ct	vecfill(10, random_value);
					typename Ct::iterator it = vecfill.begin();
					for (size_type i = 0 ; i < vecfill.size() ; i++){ os << it[i] << " "; }
					for (size_type i = 0 ; i < vecfill.size() ; i++){ os << (it[i] = replacement) << " "; }
				}
				os << std::endl;
			}

			static void		increment_decrement(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vecfill(10, random_value);
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end() ; it++) {
						os << *it << " "; *it = replacement; }
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end() ; it++)
						os << *it << " ";
					os << std::endl;
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end() ; ++it) {
						os << *it << " "; *it = replacement; }
					for (typename Ct::iterator it = vecfill.begin() ; it != vecfill.end() ; ++it)
						os << *it << " ";
					os << std::endl;
				} {
					os << " DECREMENT : org_random [" << random_value << "] - replacement [" << replacement << std::endl;;
					Ct	vecfill(10, random_value);
					for (typename Ct::iterator it = vecfill.end() - 1 ; it != vecfill.begin(); --it) {
						os << *it << " "; *it = replacement; }
					for (typename Ct::iterator it = vecfill.end() - 1 ; it != vecfill.begin(); --it)
						os << *it << " ";
					os << std::endl;
				} 
				{
					Ct	vecfill(10, random_value);
					for (typename Ct::reverse_iterator it = vecfill.rbegin() ; it != vecfill.rend() ; it++) {
						os << *it << " "; *it = replacement; }
					for (typename Ct::reverse_iterator it = vecfill.rbegin() ; it != vecfill.rend() ; it++)
						os << *it << " ";
				}
				{
					Ct	vecfill(10, random_value);
					for (typename Ct::reverse_iterator it = vecfill.rbegin() ; it != vecfill.rend() ; ++it) {
						os << *it << " "; *it = replacement; }
					for (typename Ct::reverse_iterator it = vecfill.rbegin() ; it != vecfill.rend() ; ++it)
						os << *it << " ";
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::reverse_iterator it = vecfill.rend() - 1 ; it != vecfill.rbegin() ; it--) {
						os << *it << " "; *it = replacement; }
					for (typename Ct::reverse_iterator it = vecfill.rend() - 1 ; it != vecfill.rbegin() ; it--)
						os << *it << " ";
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::reverse_iterator it = vecfill.rend() - 1 ; it != vecfill.rbegin() ; --it) {
						os << *it << " "; *it = replacement; }
					for (typename Ct::reverse_iterator it = vecfill.rend() - 1 ; it != vecfill.rbegin() ; --it)
						os << *it << " ";
				}
				os << std::endl;
			}

			static void		comparison(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vecfill(10, random_value);
					for (typename Ct::iterator it = vecfill.begin(), it2 = it ; it != vecfill.end() && (it == it2) ; it++, it2++) {
						os << *it << " "; *it = replacement; os << (it == it2) << " "; }
					for (typename Ct::iterator it = vecfill.begin(), it2 = it + 1 ; it != vecfill.end() && it != it2 ; it++, it2++) {
						os << *it << " " << (it != it2) << " "; }
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::iterator it = vecfill.begin() ; it < vecfill.end() ; it++)
						os << *it << " ";
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::reverse_iterator it = vecfill.rbegin() ; it < vecfill.rend() ; it++) {
						os << *it << " "; } }
				{

					Ct	vecfill(10, random_value);
					for (typename Ct::iterator it = vecfill.begin() ; it <= vecfill.end() - 1 ; it++)
						os << *it << " ";
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::reverse_iterator it = vecfill.rbegin() ; it <= vecfill.rend() - 1 ; it++) {
						os << *it << " "; }
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::iterator it = vecfill.end() - 1 ; it > vecfill.begin() ; it--)
						os << *it << " ";
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::reverse_iterator it = vecfill.rend() - 1 ; it > vecfill.rbegin() ; it--) {
						os << *it << " "; }
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::iterator it = vecfill.end() - 1 ; it >= vecfill.begin() ; it--)
						os << *it << " ";
				} {
					Ct	vecfill(10, random_value);
					for (typename Ct::reverse_iterator it = vecfill.rend() - 1 ; it >= vecfill.rbegin(); it--) {
						os << *it << " "; }
				}
				os << std::endl;
			}

			static void		arithmetic(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vecfill(20, random_value);
					typename Ct::iterator	it = vecfill.begin();
					for (size_type i = 0 ; (it + i) != vecfill.end() ; i++) {
						os << *(it + i) << " "; os << (*(it + i) = replacement); os << *(it + i) << " ";
						os << (it + i) - vecfill.begin() << " || " << typeid((it + i) - vecfill.begin()).name(); }
				} {
					Ct	vecfill(20, replacement);
					typename Ct::iterator	it = vecfill.begin();
					for (size_type i = vecfill.size() - 1 ; (i + it) >= vecfill.begin() ; i-- ) {
						os << *(i + it) << " "; os << (*(i + it) = random_value); os << *(i + it) << " "; 
						os << (it + i) - vecfill.begin() << " || " << typeid((it + i) - vecfill.begin()).name(); }
				} {
					Ct	vecfill(20, random_value);
					typename Ct::iterator	it = vecfill.end() - 1;
					for (size_type i = 0 ; i < vecfill.size() ; i++) {
						os << *(it - i) << " "; os << (*(it - i) = replacement); os << *(it - i) << " ";
						os << (it - i) - vecfill.begin() << " || " << typeid((it - i) - vecfill.begin()).name(); }
				} {
					Ct	vecfill(20, random_value);
					typename Ct::reverse_iterator	it = vecfill.rbegin();
					for (size_type i = 0 ; (it + i) != vecfill.rend() ; i++) {
						os << *(it + i) << " "; os << (*(it + i) = replacement); os << *(it + i) << " ";
						os << (it + i) - vecfill.rbegin() << " || " << typeid((it + i) - vecfill.rbegin()).name(); }
				} {
					Ct	vecfill(20, replacement);
					typename Ct::reverse_iterator	it = vecfill.rbegin();
					for (size_type i = vecfill.size() - 1 ; (i + it) >= vecfill.rbegin() ; i-- ) {
						os << *(i + it) << " "; os << (*(i + it) = random_value); os << *(i + it) << " "; 
						os << (it + i) - vecfill.rbegin() << " || " << typeid((it + i) - vecfill.rbegin()).name(); }
				} {
					Ct	vecfill(20, random_value);
					typename Ct::reverse_iterator	it = vecfill.rend() - 1;
					for (size_type i = 0 ; i < vecfill.size() ; i++) {
						os << *(it - i) << " "; os << (*(it - i) = replacement); os << *(it - i) << " ";
						os << (it - i) - vecfill.rbegin() << " || " << typeid((it - i) - vecfill.rbegin()).name(); }
				}
				os << std::endl;
			}

			static void		assignation(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vecfill(21, random_value);
					typename Ct::iterator	it = vecfill.begin();
					for (int i = 2, j = 0, result = 0 ; j < 5 ; j++, i++, result = *it + (*(it - 1) + *(it - 2))) {
						os << *(it += i) << " " ; *it = replacement ; os << *it << " i = " << i << " " << result ;}
				} {
					Ct	vecfill(21, random_value);
					typename Ct::iterator	it = vecfill.end() - 1;
					for (int i = 2, j = 0 ; j < 10 ; j++ ) {
						os << *(it -= i) << " " ; *it = replacement ; os << *it << " i = " << i << " "; }
				} {
					Ct	vecfill(21, random_value);
					typename Ct::reverse_iterator	it = vecfill.rbegin();
					for (int i = 2, j = 0, result = 0 ; j < 5 ; j++, i++, result = *it + (*(it - 1) + *(it - 2))) {
						os << *(it += i) << " " ; *it = replacement ; os << *it << " i = " << i << " " << result ;}
				} {
					Ct	vecfill(21, random_value);
					typename Ct::reverse_iterator	it = vecfill.rend() - 1;
					for (int i = 2, j = 0 ; j < 10 ; j++ ) {
						os << *(it -= i) << " " ; *it = replacement ; os << *it << " i = " << i << " "; }
				}
				os << std::endl;
			}

			static void		methods(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vec;
					vec.push_back(random_value);
					os << *vec.begin() << " ";
					for (int i = 0 ; i < 20 ; i++) {
						os << *vec.begin() << " ";
						vec.push_back(replacement);
						os << *(vec.begin() + i) << " ";
					}
				}
				{
					Ct vec;
					vec.push_back(random_value);
					os << *vec.begin() << " ";
					for (int i = 0 ; i < 20 ; i++) {
						vec.reserve(i);
						vec.insert(vec.begin() + i, replacement);
						os << *vec.begin() << " ";
						os << vec.end() - vec.begin() << " ";
						os << *vec.begin() + i << " ";
					}
				}
				{
					Ct vec;
					vec.push_back(random_value);
					os << *vec.begin() << " ";
					vec.reserve(10);
					for (int i = 0 ; i < 20 ; i++) {
						vec.insert(vec.begin() + i, replacement);
						os << *vec.begin() << " ";
						os << vec.end() - vec.begin() << " ";
						os << *vec.begin() + i << " ";
					}
				}
			}
		};



		void				launch_iterators() {
			ft::Random<type_value>	random;
			type_value		random_value = random.generate(type_value());
			type_value		replacement = random.generate(type_value()) / 2;
			typedef		UnitestIterators<vector_custom, std::ofstream>		iterators_custom;
			typedef		UnitestIterators<vector_original, std::ofstream>		iterators_original;

			type_file		os_std = get_folder_std().get_file("iterators");
			type_file		os_ft = get_folder_ft().get_file("iterators");

			iterators_original::constructors(*os_std, random_value, replacement);
			iterators_custom::constructors(*os_ft, random_value, replacement);
			iterators_original::accessors(*os_std, random_value, replacement);
			iterators_custom::accessors(*os_ft, random_value, replacement);
			iterators_original::increment_decrement(*os_std, random_value, replacement);
			iterators_custom::increment_decrement(*os_ft, random_value, replacement);
			iterators_original::comparison(*os_std, random_value, replacement);
			iterators_custom::comparison(*os_ft, random_value, replacement);
			iterators_original::arithmetic(*os_std, random_value, replacement);
			iterators_custom::arithmetic(*os_ft, random_value, replacement);
			iterators_original::assignation(*os_std, random_value, replacement);
			iterators_custom::assignation(*os_ft, random_value, replacement);
			iterators_original::methods(*os_std, random_value, replacement);
			iterators_custom::methods(*os_ft, random_value, replacement);
		}
};
////////////////////////////////////////////////////////////////////////////////////////////
//

#endif
