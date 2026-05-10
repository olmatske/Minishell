/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_for_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:23:09 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/10 15:25:17 by anshuval         ###   ########.fr       */
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

char	**env_array_for_execution(t_env *copied_env)
{
	char	**env_array;
	char	*tmp;
	t_env	*current;
	int		i;
	int		len;

	len = env_list_length(copied_env);
	env_array = ft_calloc((len + 1), sizeof(char *));
	if (env_array == NULL)
		return (NULL);
	current = copied_env;
	i = 0;
	while (i < len)
	{
		tmp = ft_strjoin(current->name, "=");
		if (tmp == NULL)
			return (free_env_array(env_array));
		env_array[i] = ft_strjoin(tmp, current->value);
		if (env_array[i] == NULL)
			return (free_env_array(env_array));
		free(tmp);
		current = current->next;
		i++;
	}
	return (env_array);
}

char	*find_command_path(t_cmd_node *cmd, t_env **env)
{
	char	*full_path;
	char	**directory;
	char	**env_array;

	env_array = env_array_for_execution(env);
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	while (*env_array && ft_strncmp(*env_array, "PATH=", 5) != 0)
		env_array++;
	if (*env_array == NULL)
		return (NULL);
	directory = ft_split(*env_array + 5, ':');
	if (directory == NULL)
		return (NULL);
	full_path = search_in_directories(directory, cmd);
	if (full_path == NULL)
	{
		free_env_array(env_array);
		return (NULL);
	}
	ft_free_array(directory);
	return (full_path);
}

