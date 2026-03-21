/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 18:49:22 by anshuval          #+#    #+#             */
/*   Updated: 2026/02/26 20:59:27 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

static void	free_node_env(t_env *node)
{
	if (node == NULL)
		return ;
	free(node->name);
	free(node->value);
	free(node);
}

static void	free_list_env(t_env **head)
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

static void	new_node_env(char *name, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof (t_env));
	if (new_node == NULL)
		return (NULL);
	new_node->name = name;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_env	*shell_env(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	t_env	*current;
	int		i;
	char	equal_sign;

	i = 0;
	head = NULL;
	new_node = NULL;
	current = NULL;
	if (envp == NULL || envp[0] == NULL)
		return (NULL);
	while (envp[i])
	{
		// search for the equal sign
		// left to the equal sign is the name
		// right to the equal sign is the value
		// pass both to the new node
		// append the nodes
	}
}
