# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/26 17:13:09 by olmatske          #+#    #+#              #
#    Updated: 2026/04/13 15:29:11 by anshuval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SOURCES =	minishell.c \
			env_for_execution.c \
			parsing/all_about_errors.c \
			parsing/cmd_building.c \
			parsing/grammar.c \
			parsing/list_utils_cmd.c \
			parsing/list_utils_env.c \
			parsing/list_utils_token.c \
			parsing/main_parsing.c \
			parsing/shell_env.c \
			parsing/signals.c \
			parsing/substitution_utils.c \
			parsing/substitution.c \
			parsing/tokenization.c \
			parsing/validation.c \
			parsing/debug.c

OBJECTS = $(SOURCES:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS)

fclean:
	$(RM) $(NAME) $(OBJECTS)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re