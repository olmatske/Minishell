/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:57:42 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/20 14:33:38 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int	shell_loop(t_shell *shell, t_cmd_node *cmd_list)
{
	if (!cmd_list)
		return (0);
	if (pipe_count(cmd_list))
		return (exec_pipeline(shell, cmd_list));
	return (exec_single_cmd(shell, *shell->env, cmd_list));
}

int	exec_single_cmd(t_shell *shell, t_env *environment, t_cmd_node *cmd_list)
{
	if (cmd_list->cmd->built_in_name == BUILTIN_NONE)
		return (exec_external(cmd_list->cmd, environment));
	return (wrapper_builtin(shell, cmd_list, shell->env));
}

void	free_all(t_shell *shell, t_env **env, t_cmd_node *cmd)
{
	if (cmd)
		free_cmd_list(cmd);
	if (env)
		free_env_list(env);
	if (shell)
		gc_free_all(shell);
	if (shell)
		free(shell);
}


