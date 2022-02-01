/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EnableIf.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 21:10:27 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/01 21:15:53 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft {

	template <bool Cond, class T = void> struct enable_if;

	template<> enable_if<>

}

#endif
