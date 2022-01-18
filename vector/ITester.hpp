/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ITester.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:38:05 by guhernan          #+#    #+#             */
/*   Updated: 2022/01/18 00:48:43 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITESTER_HPP
# define ITESTER_HPP

#include <string>
#include <memory>
#include <chrono>
#include <map>

class ITester {

	public:
		typedef		typename std::chrono::duration< int >				duration_type;

		typedef		typename std::map< std::string, std::ofstream *>	type_f_map;
		typedef		typename std::map< std::string, std::string >		type_fnames_map;
		typedef		typename std::map< std::string, duration_type >		type_exec_time;

		typedef		typename type_f_map::iterator						iterator_files;
		typedef		typename type_fnames_map::iterator					iterator_files_names;
		typedef		typename type_exec_time::iterator					iterator_exec_time;

////////////////////////////////////////////////////////////////////////////////////////////////

	protected:
		int					_test_nb;
		type_f_map			_files;
		type_fnames_map		_files_names;
		type_exec_time		_exec_time;
		std::string			_turn_in_directory;

		ITester() : _test_nb(0), _files(), _files_names(), _exec_time(), _turn_in_directory("./gunner_results/")
		{
		}

		ITester(const ITester &source)
			: _test_nb(source._test_nb), _files(source._files), _files_names(source._files_names),
			_exec_time(source._exec_time) {
		}

		virtual ~ITester() {
		}

	public:
		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////INIT//////////////////////////////////////////
		//
		virtual void		init_files() = 0;
		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////CONSTRUCTORS//////////////////////////////////
		//
		virtual void		unitest_constructor_empty() = 0;
		virtual void		unitest_constructor_range() = 0;
		virtual void		unitest_constructor_copy() = 0;
		virtual void		unitest_constructor_all() = 0;
		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////ACCESSORS/////////////////////////////////////
		//
		virtual int								get_test_nb() = 0;
		virtual std::string						&get_file_name(const std::string &key) = 0;
		virtual std::chrono::duration<int>		&get_exec_time(const std::string &key) = 0;
		virtual void							get_status() = 0;

		virtual void							unitest_accessors_all() = 0;
		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////CAPACITY//////////////////////////////////////
		//
		virtual void							unitest_capacity_all() = 0;
		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////MODIFIERS/////////////////////////////////////
		//
		virtual void							unitest_modifiers_all() = 0;
};

#endif
