# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/26 15:35:29 by anshuval          #+#    #+#              #
#    Updated: 2026/02/26 15:36:03 by anshuval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

MY_SOURCES		=	.c	\
					

MY_OBJECTS		=	$(MY_SOURCES:.c=.o)

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

$(NAME):	$(MY_OBJECTS)
	$(CC) $(CFLAGS) $(MY_OBJECTS) -o $(NAME)

all:	$(NAME)

clean:
	rm	-f	$(MY_OBJECTS)

fclean: clean
	rm	-f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
