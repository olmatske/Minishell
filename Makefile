# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/26 17:13:09 by olmatske          #+#    #+#              #
#    Updated: 2026/06/04 16:51:30 by anshuval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
BASE_CFLAGS = -Wall -Werror -Wextra -g3
SANITIZE ?= -fsanitize=address
SUPP_FILE = sub.sub
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=$(SUPP_FILE)

PARSING =	minishell.c \
			env_for_execution.c \
			parsing/all_about_errors.c \
			parsing/builtins.c \
			parsing/cmd_building.c \
			parsing/grammar.c \
			parsing/heredoc_utils.c \
			parsing/heredoc.c \
			parsing/list_utils_cmd.c \
			parsing/list_utils_env.c \
			parsing/list_utils_redir.c \
			parsing/list_utils_token.c \
			parsing/main_parsing.c \
			parsing/shell_env.c \
			parsing/signals.c \
			parsing/string_utils.c \
			parsing/substitution_utils.c \
			parsing/substitution.c \
			parsing/tokenization.c \
			parsing/validation.c 

EXECUTION =	execution/builtins_1.c \
			execution/builtins_2.c \
			execution/wrappers.c \
			execution/executor.c \
			execution/externals.c \
			execution/garbage_collector.c \
			execution/orchestrator.c \
			execution/pipe_helpers.c \
			execution/redirections.c \
			execution/builtin_export.c \
			execution/helpers.c \
			execution/helpers_var.c \
			execution/homeless_functions.c \
			execution/paths.c \
			execution/checkers.c

GNL =		get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c

OBJECTS = $(PARSING:.c=.o) $(EXECUTION:.c=.o) $(GNL:.c=.o)

CC = cc

CFLAGS = $(BASE_CFLAGS) $(SANITIZE)

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
fclean:
	$(RM) $(NAME) $(OBJECTS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re:
	$(MAKE) fclean
	$(MAKE) all

run: $(NAME)
	$(LSAN) ./$(NAME)

valgrind: fclean
	$(MAKE) SANITIZE= all
	valgrind $(VALGRIND_FLAGS) ./$(NAME)

.PHONY: all clean fclean re run valgrind