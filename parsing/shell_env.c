/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 18:49:22 by anshuval          #+#    #+#             */
/*   Updated: 2026/03/09 16:39:17 by anshuval         ###   ########.fr       */
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

static void	free_env_list(t_env **head)
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

static void	add_env_node_to_linked_list(t_env **head, t_env **tail, t_env *node)
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

static t_env	*create_new_env_node(char *envp)
{
	int		name_len;
	int		value_len;
	char	*equal_sign;
	t_env	*new_node;


	equal_sign = ft_strchr(envp, '=');
	name_len = equal_sign - envp;
	value_len = ft_strlen(envp) - name_len - 1;
	if (equal_sign == NULL)
		return (NULL);
	new_node = malloc(sizeof (t_env));
	if (new_node == NULL)
		return (NULL);
	new_node->name = ft_substr(envp, 0, name_len);
	if (new_node->name == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = ft_substr(envp, equal_sign + 1, value_len);
	if (new_node->value == NULL)
	{
		free(new_node->name);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

t_env	*shell_env(char **envp)
{
	int		i;
	int		j;
	t_env	*new_node;
	t_env	*head;
	t_env	*tail;

	i = 0;
	head = NULL;
	tail = NULL;
	if (envp == NULL || envp[0] == NULL)
		return (NULL);
	while (envp[i])
	{
		new_node = create_new_env_node(envp[i]);
		if (new_node == NULL)
		{
			free_env_list(&head);
			return (NULL);
		}
		add_env_node_to_linked_list(&head, &tail, new_node);
		// search for the equal sign in eac separate envp
		// left to the equal sign is the name
		// right to the equal sign is the value
		// pass both to the new node
		// append the nodes
		i++;
	}
}
