# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/09 18:24:09 by daelee            #+#    #+#              #
#    Updated: 2021/01/07 23:44:55 by daelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	= 	main.c \

LEAKS	=	-g3 -fsanitize=address

LIBFT	=	libft.a

LIBS	=	-L./Libft -lft

HEADER	=	-I./

FLAG	= 	

CC		=	gcc

RM		=	rm -rf

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
