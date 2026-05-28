/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:15:53 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/28 18:43:05 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	check_export(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	update_shell_status(t_env **env, t_shell *shell)
{
	char	*curr_status;

	curr_status = ft_itoa(shell->exit);
	if (!curr_status)
		return ;
	if (!check_var(*env, "?"))
		append_var(env, "?", curr_status);
	else
		update_var(env, "?", curr_status);
	free(curr_status);
}

char	*search_var_value(t_env *env, char *var)
{
	t_env	*curr;
	if (!check_var(env, var))
		return (NULL);
	curr = env;
	while (curr)
	{
		if (!ft_strcmp(var, curr->name))
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

void	update_pwd(t_env **env, char *new_path, char *old_path)
{
	if (!new_path || !old_path)
		return ;

	if (!check_var(*env, "PWD"))
		append_var(env, "PWD", new_path);
	else
		update_var(env, "PWD", new_path);


	if (!check_var(*env, "OLDPWD"))
		append_var(env, "OLDPWD", old_path);
	else
		update_var(env, "OLDPWD", old_path);
}
