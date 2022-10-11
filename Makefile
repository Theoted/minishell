# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/09 10:21:20 by tdeville          #+#    #+#              #
#    Updated: 2022/10/10 15:56:40 by pat              ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

include config/pars_srcs.mk 
include config/exec_srcs.mk 
include config/built_srcs.mk 

NAME	= minishell
HEADER	= includes/minishell.h libft2/include/libft2.h libft2/include/gc.h
LIBFT	= libft2

EXECINCLUDES =	-lreadline -I./readline/include

# -I./readline/include -L./readline/lib -lncurses

SRCS	+=	src/main.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -fsanitize=address -g3

all: maker ${NAME}

%.o : %.c	${HEADER}
		${CC} ${CFLAGS} -c $< -o $@

# -fsanitize=address -g3

${NAME}: ${OBJS} libft2/libft2.a
		${CC} ${CFLAGS} ${OBJS}  ${EXECINCLUDES} -o $@ libft2/libft2.a
maker:
		${MAKE} -C ${LIBFT}

clean:
		rm -f ${OBJS}
		${MAKE} clean -C ${LIBFT}

fclean:	clean
		rm -f ${NAME}
		${MAKE} fclean -C ${LIBFT}

re:		fclean all

.PHONY: all clean fclean re maker
