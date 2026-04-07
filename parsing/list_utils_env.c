/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:14:35 by anshuval          #+#    #+#             */
/*   Updated: 2026/03/31 17:58:38 by anshuval         ###   ########.fr       */
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
