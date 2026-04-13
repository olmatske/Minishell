# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/26 17:13:09 by olmatske          #+#    #+#              #
#    Updated: 2026/04/13 17:28:50 by olmatske         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = execution
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
GNL_DIR = ./get_next_line

SOURCES = files.c \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c

OBJECTS = $(SOURCES:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

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