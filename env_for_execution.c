/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_for_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:23:09 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/20 17:06:51 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_env_array(char **env_array)
{
	int	i;

	if (env_array == NULL)
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

// char	**env_array_for_execution(t_env *copied_env)
// {
// 	char	**env_array;
// 	char	*tmp;
// 	t_env	*current;
// 	int		i;
// 	int		len;

// 	len = env_list_length(copied_env);
// 	env_array = ft_calloc((len + 1), sizeof(char *));
// 	if (env_array == NULL)
// 		return (NULL);
// 	current = copied_env;
// 	i = 0;
// 	while (i < len)
// 	{
// 		tmp = ft_strjoin(current->name, "=");
// 		if (tmp == NULL)
// 			return (free_env_array(env_array));
// 		env_array[i] = ft_strjoin(tmp, current->value);
// 		if (env_array[i] == NULL)
// 			return (free_env_array(env_array));
// 		free(tmp);
// 		current = current->next;
// 		i++;
// 	}
// 	return (env_array);
// }

static int	count_env_with_value(t_env *env)
{
	int		i;
	int		count;
	t_env	*curr;

	i = 0;
	count = 0;
	curr = env;
	while (curr)
	{
		if (env->value != NULL)
			count++;
		env = env->next;
	}
	return (count);
}

char	**env_array_for_execution(t_env *copied_env)
{
	char	**env_array;
	char	*tmp;
	t_env	*curr;
	int		i;
	int		len;

	len = count_env_with_value(copied_env);
	env_array = ft_calloc((len + 1), sizeof(char *));
	if (env_array == NULL)
		return (NULL);
	curr = copied_env;
	i = 0;
	while (curr)
	{
		if (curr->value != NULL)
		{
			tmp = ft_strjoin(curr->name, "=");
			if (!tmp)
				return (free_env_array(env_array));
			env_array[i] = ft_strjoin(tmp, curr->value);
			free(tmp);
			if (!env_array[i])
				return (free_env_array(env_array));
			i++;
		}
		curr = curr->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

t_env	*copy_of_env(t_env *env)
{
	t_env	*curr;
	t_env	*new;
	t_env	*head;
	t_env	*tail;

	if (!env)
		return (NULL);
	curr = env;
	head = NULL;
	tail = NULL;
	while (curr)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		new->name = curr->name;
		new->value = curr->value;
		new->next = NULL;
		if (!head)
		{
			head = new;
			tail = new;
		}
		else
		{
			tail->next = new;
			tail = new;
		}
		curr = curr->next;
	}
	return (head);
}

// char	*find_command_path(t_cmd_node *cmd, t_env **env)
// {
// 	char	*full_path;
// 	char	**directory;
// 	char	**env_array;

// 	env_array = env_array_for_execution(env);
// 	if (ft_strchr(cmd, '/') != NULL)
// 	{
// 		if (access(cmd, X_OK) == 0)
// 			return (ft_strdup(cmd));
// 	}
// 	while (*env_array && ft_strncmp(*env_array, "PATH=", 5) != 0)
// 		env_array++;
// 	if (*env_array == NULL)
// 		return (NULL);
// 	directory = ft_split(*env_array + 5, ':');
// 	if (directory == NULL)
// 		return (NULL);
// 	full_path = search_in_directories(directory, cmd);
// 	if (full_path == NULL)
// 	{
// 		free_env_array(env_array);
// 		return (NULL);
// 	}
// 	ft_free_array(directory);
// 	return (full_path);
// }

