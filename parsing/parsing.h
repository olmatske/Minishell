/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:47:55 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/31 22:51:19 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>

# define YES	1
# define NO		0

typedef enum e_token_type {
	WORD,
	PIPE,
	IN,
	OUT,
	APPEND,
	HEREDOC
}	t_token_type;

typedef struct s_token {
	char			*value;
	int				was_quoted;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

char		*check_quotes(char *line);
void		add_node_to_token_list(t_token **head, t_token **tail,
				t_token *node);
void		add_node_to_env_list(t_env **head, t_env **tail, t_env *node);
int			env_list_length(t_env *head);
t_token		*create_new_token_node(t_token_type type, char *value);
int			linked_list_for_token(t_token **head, t_token **tail,
				t_token_type type, char *str);
int			input_validation(t_token *list);
int			handle_type(t_token **head, t_token **tail, char *line, int *i);
t_cmd_node	*cmd_building(t_token *token_list);
t_redir		*create_new_redir_node(t_token *current);
void		add_node_to_redir_list(t_redir **head, t_redir **tail,
				t_redir *node);
void		redir_builder(char **file_type, t_token *current);
int			variable_substitution(t_token **token_list, t_env *copied_env);
int			quote_status(char c, int *in_double, int *in_single);
int			malloc_args_array(t_cmd_node *new_cmd, t_token *head);
void		add_node_to_cmd_list(t_cmd_node **head, t_cmd_node **tail,
				t_cmd_node *node);
t_cmd_node	*create_empty_cmd_node(void);
void		free_args(char **args);
void		free_list_token(t_token **head);
char		*append_char(char *old_w, char c);
char		*search_env(t_env *env, char *name);
char		*append_str(char *old_w, char *suffix);
void		check_for_builtin(t_cmd_node *node);
void		just_copy(char *old_w, int *i, char **new_w);
void		expand_env(char *old_w, int *i, char **new_w, t_env *env);
char		*heredoc(char *delimiter, int was_quoted, int counter, t_env *env);
void		print_eof_warning(char *delimiter);
char		*write_to_tmp_file(char *heredoc, int counter);
int			get_delimiter_quote_status(t_token *token_list, char *delimiter);
int			start_interrupt_prompt(void);
void		end_interrupt_prompt(int copy_stdin);
char		*join_prefix(char *base, char *added, char *suffix);
void		search_dollar_or_copy(char *line, int *i, char **expand,
				t_env *env);
void		exit_status(t_env *env, int status);

#endif
