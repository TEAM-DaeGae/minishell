# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/09 18:24:09 by daelee            #+#    #+#              #
#    Updated: 2021/01/11 10:05:49 by daelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	= 	main.c \
			exec_cmds.c \
			builtins/ft_echo.c\
			builtins/ft_env.c \
			builtins/ft_pwd.c \
			builtins/ft_cd.c \
			builtins/ft_exit.c \
			
			

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
	$(CC) $(SRCS) $(LIBS) $(HEADER) $(FLAG) -o $(NAME) 

clean	:
	$(MAKE) -C ./Libft clean
	rm -rf $(OBJS)

fclean	:
	$(MAKE) -C ./Libft fclean
	rm -rf $(NAME)

re		: fclean all
