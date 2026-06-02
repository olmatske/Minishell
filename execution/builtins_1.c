/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:52:51 by olmatske          #+#    #+#             */
/*   Updated: 2026/06/02 21:29:53 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_env(t_env **env)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		if ((curr->name && ft_strncmp(curr->name, "?", 2) == 0)
			|| curr->value == NULL)
		{
			if (curr->next == NULL)
				return (1);
			curr = curr->next;
			continue ;
		}
		printf("%s=%s\n", curr->name, curr->value);
		curr = curr->next;
	}
	return (0);
}

static int	export_error(t_shell *shell, char *arg, char *name)
{
	shell->exit = 1;
	fprintf(stderr, C_RED"%s '%s': %s\n", M, arg, I);
	free(name);
	return (1);
}

static int	export_assign(t_shell *shell, t_env **env, char *arg, char **split)
{
	char	*equal;
	char	*name;
	char	*value;

	equal = ft_strchr(arg, '=');
	name = ft_substr(arg, 0, equal - arg);
	if (!name)
		return (1);
	if (!check_export(split[0]) || arg[0] == '=')
		return (export_error(shell, arg, name));
	value = ft_strdup(equal + 1);
	if (!value)
		return (free(name), 1);
	if (check_var(*env, name))
		update_var(env, name, value);
	else
		append_var(env, name, value);
	free(name);
	free(value);
	return (0);
}

int	export(t_shell *shell, t_env **env, char *arg, char **split)
{
	char	*equal;

	if (!arg)
		return (1);
	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		if (!check_export(arg) || arg[0] == '=')
			return (export_error(shell, arg, NULL));
		if (!check_var(*env, arg))
			append_var(env, arg, NULL);
		return (0);
	}
	return (export_assign(shell, env, arg, split));
}

int	unset(t_env **env, char *rm_var)
{
	t_env	*curr;
	t_env	*prev;

	if (!env || !*env || !rm_var)
		return (0);
	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strlen(curr->name) == ft_strlen(rm_var)
			&& ft_strncmp(curr->name, rm_var, ft_strlen(curr->name)) == 0)
			break ;
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return (0);
	if (!prev)
		*env = curr->next;
	else
		prev->next = curr->next;
	free(curr->name);
	free(curr->value);
	free(curr);
	return (0);
}
