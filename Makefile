# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/09 18:24:09 by daelee            #+#    #+#              #
#    Updated: 2021/01/03 18:16:08 by daelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	= 	refer_to_blog/main.c \
			refer_to_blog/convargvp.c \
			refer_to_blog/forkproc.c \
			refer_to_blog/incmdproc.c \
			refer_to_blog/pipeproc.c \
			refer_to_blog/parser.c \
			refer_to_blog/trapproc.c \

LEAKS	=	-g3 -fsanitize=address

LIBFT	=	libft.a

LIBS	=	-L./Libft -lft

HEADER	=	-I./refer_to_blog

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
