/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_building.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 14:56:40 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/27 15:07:51 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	append_redir(t_redir **head, t_redir *new)
{
	t_redir	*last;

	if (!*head)
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_redir	*new_redir(t_token *curr)
{
	t_redir	*node;

	node = ft_calloc(1, sizeof(t_redir));
	if (!node)
		ft_error("Error: Memory allocation failed\n", 1);
	if (curr->type == IN)
		redir_builder(&node->infile, curr);
	else if (curr->type == HEREDOC)
		redir_builder(&node->heredoc_delimiter, curr);
	else if (curr->type == OUT || curr->type == APPEND)
	{
		node->out_type = OUT_OVERWRITE;
		if (curr->type == APPEND)
			node->out_type = OUT_APPEND;
		redir_builder(&node->outfile, curr);
	}
	return (node);
}

