/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_for_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:23:09 by anshuval          #+#    #+#             */
/*   Updated: 2026/03/23 14:23:36 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
