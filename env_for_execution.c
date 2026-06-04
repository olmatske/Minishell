/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_for_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:23:09 by anshuval          #+#    #+#             */
/*   Updated: 2026/06/04 16:48:46 by olmatske         ###   ########.fr       */
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

static int	join(char **arr, t_env *current, int i)
{
	char	*value;
	char	*tmp;

	if (!current->value)
	{
		arr[i] = ft_strdup(current->name);
		return (arr[i] == NULL);
	}
	tmp = ft_strjoin("\"", current->value);
	if (!tmp)
		return (1);
	value = ft_strjoin(tmp, "\"");
	free(tmp);
	if (!value)
		return (1);
	tmp = ft_strjoin(current->name, "=");
	if (!tmp)
		return (free(value), 1);
	arr[i] = ft_strjoin(tmp, value);
	free(tmp);
	free(value);
	return (arr[i] == NULL);
}

char	**env_array_for_export(t_env *copied_env)
{
	char	**env_array;
	t_env	*current;
	int		i;
	int		len;

	len = env_list_length(copied_env);
	env_array = ft_calloc((len + 1), sizeof(char *));
	if (env_array == NULL)
		return (NULL);
	current = copied_env;
	i = 0;
	while (current)
	{
		if (join(env_array, current, i))
			return (free_env_array(env_array), NULL);
		current = current->next;
		i++;
	}
	return (env_array);
}

char	**env_array_for_execution(t_env *copied_env)
{
	char	**env_array;
	char	*tmp;
	t_env	*current;
	int		i;

	env_array = ft_calloc(env_list_length(copied_env) + 1, sizeof(char *));
	if (!env_array)
		return (NULL);
	current = copied_env;
	i = 0;
	while (current)
	{
		tmp = ft_strjoin(current->name, "=");
		if (!tmp)
			return (free_env_array(env_array), NULL);
		env_array[i] = ft_strjoin(tmp, current->value);
		free(tmp);
		if (!env_array[i])
			return (free_env_array(env_array), NULL);
		current = current->next;
		i++;
	}
	return (env_array);
}
