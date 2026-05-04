/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:57:42 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/04 11:41:42 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	shell_loop(t_env *environment, t_cmd_node *cmd_list)
{
	if (!cmd_list)
		return (0);
	if (has_pipe(cmd_list))
		return (exec_pipeline(environment, cmd_list));
	return (exec_single_cmd(environment, cmd_list));
}

int	has_pipe(t_cmd_node *cmd_list)
{
	t_cmd_node	*curr;
	int	i;

	curr = cmd_list;
	i = 0;
	if (curr->next)
	{
		i = 0;
		while (curr->next != NULL)
		{
			curr = curr->next;
			i++;
		}
	}
	return (i);
}

int	exec_single_cmd(t_env *environment, t_cmd_node *cmd_list)
{
	if (cmd_list->cmd->builtin == NONE_B)
		return (int exec_external(env, cmd_list->cmd));
	return (wrapper_builtin(cmd_list->cmd, environment));
	
}
