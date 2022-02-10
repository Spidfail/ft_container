# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    include.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guhernan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/10 17:14:32 by guhernan          #+#    #+#              #
#    Updated: 2022/02/10 17:26:56 by guhernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_INC_TEST_V			:=	VectorAccessorsTests.hpp \
						VectorCapacityTests.hpp \
						VectorConstructorTests.hpp \
						VectorIteratorsTests.hpp \
						VectorModifiersTests.hpp

# _INC_TEST_V_PATH	:=	$(addprefix $(_INC_TEST_V_DIR)/, $(_INC_TEST_V))
# 
# _INC_TEST_M_PATH	:=	$(addprefix $(_INC_TEST_M_DIR)/, $(_INC_TEST_M))
# 
# _INC_TEST_S_PATH	:=	$(addprefix $(_INC_TEST_S_DIR)/, $(_INC_TEST_S))
