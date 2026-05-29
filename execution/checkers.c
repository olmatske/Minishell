/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:15:53 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/29 11:51:20 by olmatske         ###   ########.fr       */
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

int	echo_n_check(char **str)
{
	int	i;
	int	k;
	int	found;

	i = 1;
	k = 0;
	found = 0;
	while (str[i])
	{
		if (str[i][0] != '-')
			break ;
		k = 1;
		while (str[i][k] == 'n')
			k++;
		if (str[i][k] == '\0')
		{
			i++;
			found = 1;
		}
		else
			break ;
	}
	return (found);
}
