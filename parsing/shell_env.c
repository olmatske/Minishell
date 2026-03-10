/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 18:49:22 by anshuval          #+#    #+#             */
/*   Updated: 2026/03/10 11:30:01 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

static t_env	*create_new_env_node(char *envp)
{
	char	*equal_sign;
	t_env	*new_node;

	equal_sign = ft_strchr(envp, '=');
	if (equal_sign == NULL)
		return (NULL);
	new_node = malloc(sizeof (t_env));
	if (new_node == NULL)
		return (NULL);
	new_node->name = ft_substr(envp, 0, (equal_sign - envp));
	if (new_node->name == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = ft_strdup(equal_sign + 1);
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
		add_node_to_env_list(&head, &tail, new_node);
		i++;
	}
	return (head);
}
