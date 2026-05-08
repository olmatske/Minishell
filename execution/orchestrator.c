/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:57:42 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/08 13:18:41 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// add shell loop to minishell.h !!!!!!!!!!!!
int	shell_loop(t_shell *shell, t_cmd_node *cmd_list)
{
	if (!cmd_list)
		return (0);
	if (pipe_count(cmd_list))
		return (exec_pipeline(shell, cmd_list));
	return (exec_single_cmd(shell->env, cmd_list));
}

// add shell struct

int	exec_single_cmd(t_env *environment, t_cmd_node *cmd_list)
{
	if (cmd_list->cmd->builtin == NONE_B)
		return (exec_external(env, cmd_list->cmd));
	return (wrapper_builtin(cmd_list->cmd, environment));
}
