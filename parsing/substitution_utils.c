/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:30:55 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/31 22:33:14 by anshuval         ###   ########.fr       */
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

void	search_dollar_or_copy(char *line, int *i, char **expand, t_env *env)
{
	if (line[*i] == '$')
		expand_env(line, i, expand, env);
	else
		just_copy(line, i, expand);
}

void	exit_status(t_env *env, int status)
{
	char	*status_str;

	while (env)
	{
		if (ft_strncmp(env->name, "?", 2) == 0)
		{
			status_str = ft_itoa(status);
			if (status_str == NULL)
				return ;
			free(env->value);
			env->value = status_str;
			return ;
		}
		env = env->next;
	}
}
