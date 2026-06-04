/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 14:56:40 by olmatske          #+#    #+#             */
/*   Updated: 2026/06/04 21:32:15 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	redir_builder(char **target_name, t_token *current)
{
	if (*target_name != NULL)
		free(*target_name);
	if (current->next == NULL || current->next->type == IN
		|| current->next->type == OUT || current->next->type == APPEND
		|| current->next->type == HEREDOC)
	{
		ft_putstr_fd(C_RED"Syntax error near unsexpected token 'newline'\n"C_RESET, 2);
		return ;
	}
	*target_name = ft_strdup(current->next->value);
	if (*target_name == NULL)
		ft_error("Error: Memory allocation failed\n", 1);
}

t_redir	*create_new_redir_node(t_token *current)
{
	t_redir	*node;

	node = ft_calloc(1, sizeof(t_redir));
	if (node == NULL)
		ft_error("Error: Memory allocation failed\n", 1);
	if (current->type == IN)
		redir_builder(&node->infile, current);
	else if (current->type == HEREDOC)
		redir_builder(&node->heredoc_delimiter, current);
	else if (current->type == OUT || current->type == APPEND)
	{
		node->out_type = OUT_OVERWRITE;
		if (current->type == APPEND)
			node->out_type = OUT_APPEND;
		redir_builder(&node->outfile, current);
	}
	return (node);
}

void	add_node_to_redir_list(t_redir **head, t_redir **tail, t_redir *node)
{
	if (*head == NULL)
	{
		*head = node;
		*tail = node;
	}
	else
	{
		(*tail)->next = node;
		*tail = node;
	}
}

void	free_redir_list(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		if (redir->heredoc_delimiter != NULL && redir->infile != NULL)
			unlink(redir->infile);
		free(redir->heredoc_delimiter);
		free(redir->infile);
		free(redir->outfile);
		free(redir);
		redir = next;
	}
}
