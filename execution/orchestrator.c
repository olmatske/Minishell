/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:57:42 by olmatske          #+#    #+#             */
/*   Updated: 2026/06/02 15:01:22 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	shell_loop(t_shell *shell, t_cmd_node *cmd_list)
{
	if (!cmd_list)
		return (0);
	if (pipe_count(cmd_list))
		return (exec_pipeline(shell, cmd_list));
	return (exec_single_cmd(shell, *shell->env, cmd_list));
}

// > test hangs somewhere, idk how to fix it :,)
int	exec_single_cmd(t_shell *shell, t_env *env, t_cmd_node *cmd_list)
{
	int	saved_in;
	int	saved_out;

	if (cmd_list->cmd->built_in_name == BUILTIN_NONE
		&& (!cmd_list->cmd->args || !cmd_list->cmd->args[0]))
	{
		saved_in = dup(STDIN_FILENO);
		saved_out = dup(STDOUT_FILENO);
		shell->exit = wrapper_redirections(cmd_list->cmd->redir);
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		update_shell_status(shell->env, shell);
		return (shell->exit);
	}
	if (cmd_list->cmd->built_in_name != BUILTIN_NONE)
	{
		shell->exit = wrapper_all(shell, cmd_list, shell->env, 0);
		update_shell_status(shell->env, shell);
		return (shell->exit);
	}
	shell->exit = exec_external(shell, cmd_list->cmd, env);
	update_shell_status(shell->env, shell);
	return (shell->exit);
}
