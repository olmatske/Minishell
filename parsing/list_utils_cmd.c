/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:33:49 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/30 22:07:41 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free (args[i]);
		i++;
	}
	free(args);
}

void	free_cmd_list(t_cmd_node *head)
{
	t_cmd_node	*current;
	t_cmd_node	*next;

	if (head == NULL)
		return ;
	current = head;
	while (current)
	{
		next = current->next;
		if (current->cmd)
		{
			if (current->cmd->args)
				free_args(current->cmd->args);
			if (current->cmd->redir)
				free_redir_list(current->cmd->redir);
			free(current->cmd);
		}
		free(current);
		current = next;
	}
}

t_cmd_node	*create_empty_cmd_node(void)
{
	t_cmd_node	*new_node;

	new_node = ft_calloc(1, sizeof (t_cmd_node));
	if (new_node == NULL)
		return (NULL);
	new_node->cmd = ft_calloc(1, sizeof (t_cmd));
	if (new_node->cmd == NULL)
		return (free(new_node), NULL);
	new_node->cmd->built_in_name = BUILTIN_NONE;
	return (new_node);
}

void	add_node_to_cmd_list(t_cmd_node **head, t_cmd_node **tail,
		t_cmd_node *node)
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

int	malloc_args_array(t_cmd_node *new_cmd, t_token *head)
{
	int		len;
	t_token	*current;

	len = 0;
	current = head;
	while (current != NULL && current->type != PIPE)
	{
		if (current->type == WORD)
			len++;
		else if (current->type == IN || current->type == OUT
			|| current->type == APPEND || current->type == HEREDOC)
		{
			if (current->next != NULL)
				current = current->next;
		}
		current = current->next;
	}
	new_cmd->cmd->args = ft_calloc((len + 1), sizeof (char *));
	if (new_cmd->cmd->args == NULL)
		return (free(new_cmd), -1);
	return (0);
}
