/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:31:35 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/31 14:01:36 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*create_new_token_node(t_token_type type, char *value)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof (t_token));
	if (new_node == NULL)
		return (NULL);
	new_node->value = ft_strdup(value);
	if (new_node->value == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->type = type;
	return (new_node);
}

int	linked_list_for_token(t_token **head, t_token **tail,
	t_token_type type, char *str)
{
	t_token	*new_node;

	new_node = create_new_token_node(type, str);
	if (new_node == NULL)
	{
		free_list_token(head);
		return (-1);
	}
	add_node_to_token_list(head, tail, new_node);
	return (0);
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
