/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorTesterUtils.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:34:13 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/08 13:07:53 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft {

	template <class Ct, typename Os>
		struct TesterUtils {

			static void		print_state(Os &os, Ct vector) { os << vector.size() << "|" << vector.capacity(); }

			static void		print_content(Os &os, Ct vector) {
				for (typename Ct::size_type i = 0 ; i < vector.size() ; i++) {
					os << vector[i] << " ";
				}
			}

			private:
			TesterUtils() { }
			~TesterUtils() { }
			TesterUtils(const TesterUtils &source) { (void) source; }
			TesterUtils		operator=(const TesterUtils &source) { (void)source; }

		};
}
