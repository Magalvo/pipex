# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 16:18:50 by dde-maga          #+#    #+#              #
#    Updated: 2024/04/22 19:01:31 by dde-maga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex 

LIB_SRCS =  ft_strlen.c ft_putchar_fd.c ft_putstr_fd.c ft_memset.c \
			ft_calloc.c ft_strdup.c ft_itoa.c ft_split.c \
			ft_strncmp.c ft_substr.c ft_strjoin.c 
SRC_GNL =	gnl_utils.c gnl.c

SRC =	$(addprefix ./lib/, $(LIB_SRCS)) \
		$(addprefix ./lib/gnl/, $(SRC_GNL))\

SRCOBJ = obj/
CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJ = $(addprefix $(SRCOBJ), $(SRC:./lib/%.c=%.o))

all: $(NAME)

$(NAME): $(OBJ)
	@${CC} ${CFLAGS} -g3 normal_pipex.c ${OBJ} -o $(NAME)

$(SRCOBJ)%.o: lib/%.c
	@mkdir -p $(SRCOBJ)
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@rm -rf $(SRCOBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

