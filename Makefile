# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guhernan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 20:20:51 by guhernan          #+#    #+#              #
#    Updated: 2022/02/09 21:54:03 by guhernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= ft_container
CC			:= clang++
CFLAGS		:= -Wall -Wextra -Werror

OBJ_DIR		:= objs
SRC_DIR		:= srcs
VECTOR_DIR	:= vector
MAP_DIR		:= map
STACK_DIR	:= stack


SRCS		:= EnableIf.hpp \
			   IsIntegral.hpp \
			   CompareUtils.hpp

VECTOR_SRCS	:=
MAP_SRCS	:=
STACK_SRCS	:=

include $(VECTOR_DIR)/include.mk
include $(MAP_DIR)/include.mk
include $(STACK_DIR)/include.mk

################################################################################

all: $(NAME)

$(NAME) :	$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

