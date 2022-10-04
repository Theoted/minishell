# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/09 10:21:20 by tdeville          #+#    #+#              #
#    Updated: 2022/10/04 08:28:56 by tdeville         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

include config/pars_srcs.mk 
include config/exec_srcs.mk 

NAME	= minishell
HEADER	= includes/minishell.h libft2/include/libft2.h libft2/include/gc.h
LIBFT	= libft2

EXECINCLUDES =	-lreadline -I./readline/include -L./readline/lib -lncurses

# -I./readline/include -L./readline/lib -lncurses

SRCS	+=	main.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc
CFLAGS	= 

all: maker ${NAME}

%.o : %.c	${HEADER}
		${CC} ${CFLAGS} -c $< -o $@

# -fsanitize=address -g3

${NAME}: ${OBJS} libft2/libft2.a
		${CC} ${CFLAGS} ${OBJS}  ${EXECINCLUDES} -o $@ libft2/libft2.a -fsanitize=address -g3

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
