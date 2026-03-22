# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/26 17:13:09 by olmatske          #+#    #+#              #
#    Updated: 2026/03/22 18:36:11 by olmatske         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = execution

SOURCES = builtin.c

OBJECTS = $(SOURCES:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(NAME) -lreadline

%.o: %.c execution.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS)

fclean:
	$(RM) $(NAME) $(OBJECTS)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re