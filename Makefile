# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/09 18:24:09 by daelee            #+#    #+#              #
#    Updated: 2021/01/09 15:38:50 by daelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	= 	main.c \
			exec_cmds.c \
			builtins/echo.c\
			builtins/env.c \
			builtins/pwd.c \
			builtins/cd.c \
			
			

LEAKS	=	-g3 -fsanitize=address

LIBFT	=	libft.a

LIBS	=	-L./Libft -lft

HEADER	=	-I./

FLAG	= 	

CC		=	gcc

RM		=	rm -rf

DEBUG	=	-g -fsanitize=address

all		: $(NAME)

$(LIBFT):
	$(MAKE) -C ./Libft

$(NAME)	: $(LIBFT)
	$(CC) $(SRCS) $(LIBS) $(HEADER) $(FLAG) $(DEBUG) -o $(NAME) 

clean	:
	$(MAKE) -C ./Libft clean
	rm -rf $(OBJS)

fclean	:
	$(MAKE) -C ./Libft fclean
	rm -rf $(NAME)

re		: fclean all
