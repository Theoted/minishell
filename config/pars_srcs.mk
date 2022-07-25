# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pars_srcs.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/09 14:45:32 by tdeville          #+#    #+#              #
#    Updated: 2022/07/25 13:12:46 by tdeville         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRCS +=	src/p_bin_path.c \
		src/p_utils.c \
		src/p_lexer.c \
		src/p_here_doc.c \
		src/p_here_doc_utils.c \
		src/p_expend_vars.c \
		src/p_clear_hd.c \
		src/p_synthax_checker.c \
		src/b_init.c \
		src/b_unset.c \
		src/b_exit.c \
		src/b_export.c \
		src/b_cd.c \
		src/b_echo.c \
		src/b_echo_envvar.c \
		src/b_exec_built_ins.c \
		src/b_utils.c 