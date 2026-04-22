/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_for_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:23:09 by anshuval          #+#    #+#             */
/*   Updated: 2026/04/16 13:01:24 by anshuval         ###   ########.fr       */
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
