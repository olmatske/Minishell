/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 18:49:22 by anshuval          #+#    #+#             */
/*   Updated: 2026/03/22 20:46:21 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

char	**free_env_array(char **env_array)
{
	int	i;

	if(env_array == NULL)
		return (NULL);
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
	return (NULL);
}

char	**env_array_for_execution(t_env *copied_env)
{
	char	**env_array;
	t_env	*current;
	int		i;
	int		len;

	len = env_list_length(copied_env);
	env_array = malloc(sizeof(char *) * (len + 1));
	if (env_array == NULL)
		return (NULL);
	current = copied_env;
	i = 0;
	while (i < len)
	{
		env_array[i] = ft_strjoin(current->name, "=");
		if (env_array[i] == NULL)
			return (free_env_array(env_array));
		env_array[i] = ft_strjoin(env_array[i], current->value);
		if (env_array[i] == NULL)
			return (free_env_array(env_array));
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

static void get_new_shlvl(t_env **head)
{
	int		level;
	char	*new_shlvl;
	t_env	*current;

	current = *head;
	while (current)
	{
		if (ft_strncmp(current->name, "SHLVL", 5) == 0)
		{
			level = ft_atoi(current->value);
			free(current->value);
			level++;
			new_shlvl = ft_itoa(level);
			if (new_shlvl == NULL)
				return ;
			current->value = new_shlvl;
			return ;
		}
		current = current->next;
	}
}

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

static t_env	*shell_env(char **envp)
{
	int		i;
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
	get_new_shlvl(&head);
	return (head);
}
