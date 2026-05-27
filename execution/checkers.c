/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:15:53 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/27 21:40:44 by olmatske         ###   ########.fr       */
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
		append_variable(env, "?", curr_status);
	else
		update_variable(env, "?", curr_status);
	free(curr_status);
}

// int	is_var_explansion(char *str)
// {
// 	if ()
// }
