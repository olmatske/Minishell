/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:14:35 by anshuval          #+#    #+#             */
/*   Updated: 2026/03/23 14:38:23 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

void	free_env_list(t_env **head)
{
	t_env	*current;
	t_env	*next;

	if (head == NULL || (*head) == NULL)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	free_list_token(t_token **head)
{
	t_token	*current;
	t_token	*next;

	if (head == NULL || (*head) == NULL)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	add_node_to_token_list(t_token **head, t_token **tail, t_token *node)
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

void	add_node_to_env_list(t_env **head, t_env **tail, t_env *node)
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

int	env_list_length(t_env *head)
{
	int		len;
	t_env	*current;

	len = 0;
	current = head;
	while (current)
	{
		len++;
		current = current->next;
	}
	return (len);
}

static void	free_args(char **args)
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
			free(current->cmd->redir);
			free(current->cmd);
		}
		free(current);
		current = next;
	}
}
