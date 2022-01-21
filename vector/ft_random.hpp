/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:02:30 by guhernan          #+#    #+#             */
/*   Updated: 2022/01/21 21:23:19 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RANDOM_HPP
# define FT_RANDOM_HPP
# include <string>

namespace ft {

	template < typename T >
		class Random {
			public:
				typedef		T		type_value;

			private:
				type_value		_rand_collection;

			public:
				Random() { init_random_collection(type_value()); }
				Random(const Random &source) : _rand_collection(source._rand_collection) { }
				~Random() { }
				Random	&operator=(const Random &source) { _rand_collection = source.get_collection(); }

				type_value		get_collection() {
					return _rand_collection;
				}
				void			init_random_collection(type_value);
				type_value		generate( type_value, unsigned short int len = 0);
		};
}

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////FUNCTION TEMPLATE SPECIALISATION/////////////////////////
//
/////////////////////////////////////////////RANDOMISATION//////////////////////////////////
//
template <> void			ft::Random<std::string>::init_random_collection(std::string) {
	_rand_collection.reserve(127 - 33);
	std::string::iterator	it = _rand_collection.begin();

	for (int c = 33 ; it != _rand_collection.end() && c < 127 ; it++, c++) {
		*it = c;
	}
}

template <> void			ft::Random<int>::init_random_collection(int) {
	_rand_collection = 100000;
}

template <> std::string		ft::Random<std::string>::generate(std::string, unsigned short int len) {
	std::string		tmp;
	std::srand(time(NULL));
	tmp.reserve(len);

	for (int i = 0; i < len; ++i) {
		tmp += _rand_collection[std::rand() % (sizeof(_rand_collection) - 1)];
	}
	return tmp;
}

template <> int				ft::Random<int>::generate(int, unsigned short int len) {
	(void)len;
	std::srand(time(NULL));
	int rand_nb;

	for (rand_nb = rand() ; rand_nb == 0 ; rand_nb = rand()) { }
	return rand_nb % _rand_collection + 1;
}

#endif
