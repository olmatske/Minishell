/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:57:42 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/29 11:47:22 by olmatske         ###   ########.fr       */
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

static int	wrapper_all(t_shell *shell, t_cmd_node *n, t_env **env, int exit)
{
	int		save_in;
	int		save_out;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (save_in < 0 || save_out < 0)
		return (perror("wrapper dup2"), 1);
	if (n->cmd->redir && (n->cmd->redir->infile || n->cmd->redir->outfile))
	{
		exit = wrapper_redirections(n->cmd->redir);
		if (exit != 0)
		{
			dup2(save_in, STDIN_FILENO);
			dup2(save_out, STDOUT_FILENO);
			close(save_in);
			close(save_out);
			return (exit);
		}
	}
	exit = wrapper_builtins(shell, n, env);
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
	return (exit);
}

int	exec_single_cmd(t_shell *shell, t_env *env, t_cmd_node *cmd_list)
{
	int	status;

	status = 0;
	if (cmd_list->cmd->built_in_name == BUILTIN_NONE)
		status = exec_external(shell, cmd_list->cmd, env);
	else
		status = wrapper_all(shell, cmd_list, shell->env, 0);
	shell->exit = status;
	update_shell_status(shell->env, shell);
	return (status);
}

void	free_all(t_shell *shell, t_env **env, t_cmd_node *cmd)
{
	(void)env;
	if (cmd)
		free_cmd_list(cmd);
	if (shell)
		gc_free_all(shell);
	if (shell)
		free(shell);
}
