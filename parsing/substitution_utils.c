/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:30:55 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/31 18:22:46 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	just_copy(char *old_w, int *i, char **new_w)
{
	*new_w = append_char(*new_w, old_w[*i]);
	(*i)++;
}

void	expand_env(char *old_w, int *i, char **new_w, t_env *env)
{
	int		start;
	char	*name;
	char	*value;

	(*i)++;
	if (old_w[*i] == '\0' || old_w[*i] == ' ' || old_w[*i] == '\t'
		|| old_w[*i] == '\'' || old_w[*i] == '\"')
	{
		*new_w = append_char(*new_w, '$');
		return ;
	}
	start = *i;
	if (old_w[*i] == '?')
		(*i)++;
	else
	{
		while (old_w[*i] && (ft_isalnum(old_w[*i]) || old_w[*i] == '_'))
			(*i)++;
	}
	name = ft_substr(old_w, start, *i - start);
	value = search_env(env, name);
	free(name);
	*new_w = append_str(*new_w, value);
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

char	*append_str(char *old_w, char *suffix)
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

char	*join_prefix(char *base, char *add, char *suffix)
{
	char	*tmp;
	char	*result;

	tmp = append_str(base, suffix);
	if (tmp == NULL)
		return (free(add), NULL);
	result = append_str(tmp, add);
	free(add);
	return (result);
}
