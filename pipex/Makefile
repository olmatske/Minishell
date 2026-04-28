# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/12 13:59:17 by anshuval          #+#    #+#              #
#    Updated: 2026/01/19 22:01:52 by anshuval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex

MY_SOURCES		=	pipex.c	\
					children.c \
					all_about_errors.c	\
					validation.c	\
					./libft_utils/ft_putstr_fd.c	\
					./libft_utils/ft_split.c	\
					./libft_utils/ft_strjoin.c	\
					./libft_utils/ft_strlen.c	\
					./libft_utils/ft_strncmp.c	\
					./libft_utils/ft_substr.c	\
					./libft_utils/ft_strdup.c	\
					./libft_utils/ft_strchr.c

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
