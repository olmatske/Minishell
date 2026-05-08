# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/26 17:13:09 by olmatske          #+#    #+#              #
#    Updated: 2026/05/08 13:02:50 by olmatske         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

PARSING =	minishell.c \
			env_for_execution.c \
			parsing/all_about_errors.c \
			parsing/builtins.c \
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

EXECUTION =	execution/builtin.c \
			execution/checkers.c \
			execution/executor.c \
			execution/externals.c \
			execution/garbace_collector.c \
			execution/main_execution.c \
			execution/orchestrator.c \
			execution/path.c \
			execution/pipe_helpers.c \
			execution/pipes.c \
			execution/redirections.c

GNL =		get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c

OBJECTS = $(PARSING:.c=.o) $(EXECUTION:.c=.o) $(GNL:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3

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
	$(MAKE) -C $(LIBFT_DIR) fclean

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re