/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:47:55 by anshuval          #+#    #+#             */
/*   Updated: 2026/03/22 20:46:13 by anshuval         ###   ########.fr       */
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

int		check_quotes(char *line);
void	free_env_list(t_env **head);
void	free_list_token(t_token **head);
void	add_node_to_token_list(t_token **head, t_token **tail, t_token *node);
void	add_node_to_env_list(t_env **head, t_env **tail, t_env *node);
int		env_list_length(t_env *head);
void	print_token_list_debug(t_token *head);

#endif
