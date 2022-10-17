# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 16:45:37 by rmattheo          #+#    #+#              #
#    Updated: 2022/10/17 17:59:34 by tdeville         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	= libft2.a

HEADER	=	include/gc.h		\
			include/libft.h
INCLUDES= ${addprefix -I, ${sort ${dir ${HEADER}}}}

SRCS	=	ft_check/ft_isalpha.c			\
			ft_check/ft_isdigit.c			\
			ft_check/ft_isalnum.c			\
			ft_check/ft_isascii.c			\
			ft_check/ft_isprint.c			\
			ft_check/ft_toupper.c			\
			ft_check/ft_tolower.c			\
			ft_mem/ft_memset.c				\
			ft_mem/ft_memcpy.c				\
			ft_mem/ft_memmove.c				\
			ft_mem/ft_memchr.c				\
			ft_mem/ft_memcmp.c				\
			ft_atoi_itoa/ft_itoa.c			\
			ft_atoi_itoa/gc_itoa.c			\
			ft_atoi_itoa/ft_atoi.c			\
			ft_atoi_itoa/ft_atoi_base.c		\
			ft_str/ft_strlen.c			\
			ft_str/ft_strchr.c			\
			ft_str/ft_strncmp.c			\
			ft_str/ft_strnstr.c			\
			ft_str/ft_strrchr.c			\
			ft_str/ft_strlcat.c			\
			ft_str/ft_strlcpy.c			\
			ft_str/ft_strdup.c 			\
			ft_str/ft_substr.c			\
			ft_str/ft_strtrim.c			\
			ft_str/ft_strmapi.c			\
			ft_str/ft_strmapi.c			\
			ft_str/ft_striteri.c		\
			ft_str/ft_split.c			\
			ft_str/ft_strjoin.c			\
			ft_str/ft_strlen_charset.c	\
			ft_str/gc_split.c			\
			ft_str/gc_split_spaces.c 	\
			ft_str/gc_substr.c			\
			ft_str/gc_strjoin.c			\
			ft_str/gc_strdup.c			\
			ft_str/gc_strtrim.c			\
			ft_malloc/ft_bzero.c			\
			ft_malloc/ft_calloc.c			\
			ft_malloc/gc_calloc.c			\
			ft_put/ft_putchar_fd.c			\
			ft_put/ft_putnbr_fd.c			\
			ft_put/ft_putstr_fd.c			\
			ft_put/ft_putptr.c				\
			ft_put/ft_putnbr_usigned_fd.c	\
			ft_put/ft_putnbr_base.c			\
			ft_put/ft_putendl_fd.c			\
			ft_gnl/get_next_line.c			\
			ft_gnl/gc_get_next_line.c		\
			ft_maths/ft_round.c				\
			ft_maths/ft_colinterpolate.c	\
			ft_lst/ft_lstnew.c				\
			ft_lst/ft_lstadd_front.c		\
			ft_lst/ft_lstlast.c			\
			ft_lst/ft_lstadd_back.c		\
			ft_lst/ft_lstdelone.c		\
			ft_lst/ft_lstclear.c		\
			ft_lst/ft_lstiter.c			\
			ft_lst/ft_lstmap.c			\
			ft_lst/ft_lstsize.c			\
			ft_gc/gc_add_mal.c			\
			ft_gc/gc_lstadd_front.c		\
			ft_gc/gc_lstnew.c			\
			ft_gc/gc_free_all.c			\
			ft_gc/gc_free_malloc.c		\
			ft_gc/gc_free_malloc_split.c\
			ft_gc/gc_lstdelone.c


OBJS    = ${SRCS:.c=.o}

CC        = gcc

CFLAGS    = -Wall -Wextra -Werror

%o : %c ${HEADER} Makefile
		${CC} ${CFLAGS} -c $< -o $@

${NAME}:    ${OBJS}
		ar -rcs ${NAME} ${OBJS}

all:    ${NAME}

clean:
		rm -f ${OBJS}

fclean:    clean
		rm -f ${NAME}

re:        fclean all

.PHONY:    all clean fclean re
