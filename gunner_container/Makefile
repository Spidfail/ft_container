# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guhernan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 22:18:19 by guhernan          #+#    #+#              #
#    Updated: 2022/02/10 17:27:23 by guhernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:= gunner_container
CC					:= clang++
CFLAGS				:= -Wall -Wextra -Werror -O2

OBJ_DIR				:= gunner_objs
SRCS_DIR			:= gunner_srcs

################################################################################

_RES_TEST_DIR		:= gunner_results
_INC_TEST_DIR		:= tests
_INC_TEST_V_DIR		:= $(_INC_TEST_DIR)/vector
_INC_TEST_M_DIR		:= $(_INC_TEST_DIR)/map
_INC_TEST_S_DIR		:= $(_INC_TEST_DIR)/stack

_SRCS_GUNNER		:=
_SRCS_GUNNER_PATH	:=
include $(SRCS_DIR)/include.mk

_INC_TEST_V			:= 
_INC_TEST_V_PATH	:= 
_INC_TEST_M			:=
_INC_TEST_M_PATH	:= 
_INC_TEST_S			:=
_INC_TEST_S_PATH	:= 
include $(SRCS_DIR)/$(_INC_TEST_DIR)/include.mk


_INC_TESTS_PATH			:= $(_INC_TEST_V_PATH) $(_INC_TEST_M_PATH) $(_INC_TEST_S_PATH)
_INC_TEST_DIR			:= $(_INC_TEST_V_DIR) $(_INC_TEST_M_DIR) $(_INC_TEST_S_DIR)

################################################################################

_TESTED_CONTAINER		:= $(shell find .. -path '../gunner_container' -type d -prune -o -name "*.*pp" -type f -print)
_INC_CONTAINER_PATH		:= $(filter %.hpp, $(_TESTED_CONTAINER))
_SRCS_CONTAINER_PATH	:= $(filter %.cpp, $(_TESTED_CONTAINER))

_CONTAINER_DIR			:= $(dir $(_INC_CONTAINER_PATH) $(_SRCS_CONTAINER_PATH))
#_INC_CONTAINER			:= $(notdir $(_INC_CONTAINER_PATH))
#_SRCS_CONTAINER		:= $(notdir $(_SRCS_CONTAINER_PATH))

################################################################################

_INCLUDE_DIR		:= $(addprefix -I,$(_INC_TEST_DIR) $(_CONTAINER_DIR))
_REQUIRED_DIR		:= $(_RES_TEST_DIR) $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(_INC_TEST_DIR) $(_CONTAINER_DIR))


INC					:= $(_INC_TESTS_PATH) $(_INC_CONTAINER_PATH)
SRCS				:= $(_SRCS_GUNNER_PATH) $(_SRCS_CONTAINER_PATH)
OBJS				:= $(SRCS:.cpp=.o)

################################################################################

all:				$(NAME)

$(NAME):			$(OBJS)
	$(CC) $< -o $@

$(OBJ_DIR)/%.o:		%.cpp $(INC) | $(_REQUIRED_DIR)
	$(CC) $(CFLAGS) $(_INCLUDE_DIR)  -c $< -o $@

$(_REQUIRED_DIR) :
		mkdir -p $(_REQUIRED_DIR)
