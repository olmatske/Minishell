/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:47:55 by anshuval          #+#    #+#             */
/*   Updated: 2026/04/07 15:29:10 by anshuval         ###   ########.fr       */
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
	t_token_type	type;
	struct s_token	*next;
}	t_token;

int			check_quotes(char *line);
void		free_env_list(t_env **head);
void		free_list_token(t_token **head);
void		add_node_to_token_list(t_token **head, t_token **tail,
				t_token *node);
void		add_node_to_env_list(t_env **head, t_env **tail, t_env *node);
int			env_list_length(t_env *head);
void		print_token_list_debug(t_token *head);
t_token		*create_new_token_node(t_token_type type, char *value);
int			linked_list_for_token(t_token **head, t_token **tail,
				t_token_type type, char *str);
int			input_validation(t_token *list);
int			handle_type(t_token **head, t_token **tail, char *line, int *i);
t_cmd_node	*cmd_building(t_token *token_list);
void		variable_substitution(t_token *token_list, t_env *copied_env);
int			quote_status(char c, int *in_double, int *in_single);

#endif
