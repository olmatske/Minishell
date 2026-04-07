/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:30:55 by anshuval          #+#    #+#             */
/*   Updated: 2026/04/07 16:49:39 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

char	*append_str(char *old_w, char suffix)
{
	char	*new_w;

	if (suffix == NULL)
		return (old_w);
	if (old_w == NULL)
		return (ft_strdup(suffix));
	new_w = ft_strjoin(old_w, suffix);
	free(old_w);
	return (new_w);
}

char	*search_env(t_env *env, char *name)
{
	int	len;

	len = ft_strlen(name) + 1;
	while (env)
	{
		if (ft_strncmp(env->name, name, len) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*append_char(char *old_w, char c)
{
	char	*new_w;
	int		len;

	len = 0;
	if (old_w != NULL)
		len = ft_strlen(old_w);
	new_w = malloc(len + 2);
	if (new_w == NULL)
	{
		free(old_w);
		return (NULL);
	}
	if (old_w != NULL)
		ft_strlcpy(new_w, old_w, len + 1);
	new_w[len] = c;
	new_w[len + 1] = '\0';
	free(old_w);
	return (new_w);
}
