# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/09 10:21:20 by tdeville          #+#    #+#              #
#    Updated: 2022/07/05 14:36:15 by theodeville      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include config/pars_srcs.mk 
include config/exec_srcs.mk 

NAME	= minishell
HEADER	= includes/minishell.h libft2/include/libft2.h libft2/include/gc.h
LIBFT	= libft2

EXECINCLUDES =	-lreadline

# -I./readline/include -L./readline/lib -lncurses

SRCS	+=	src/e_main.c	\
			src/e_exec.c	\
			src/e_execve.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc
CFLAGS	= 

all: maker ${NAME}

%.o : %.c	${HEADER}
		${CC} ${CFLAGS} -c $< -o $@


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