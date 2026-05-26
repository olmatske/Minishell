/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:57:42 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/26 12:59:01 by olmatske         ###   ########.fr       */
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

static int	wrapper_all(t_shell *shell, t_cmd_node *node, t_env **env, int status)
{
	int		save_in;
	int		save_out;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (save_in < 0 || save_out < 0)
		return (perror("wrapper dup2"), 1);
	if (node->cmd->redir && (node->cmd->redir->infile || node->cmd->redir->outfile))
	{
		status = wrapper_redirections(node->cmd->redir);
		if (status != 0)
		{
			dup2(save_in, STDIN_FILENO);
			dup2(save_out, STDOUT_FILENO);
			close(save_in);
			close(save_out);
			return (status);
		}
	}
	status = wrapper_builtin(shell, node, env);
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
	return (status);
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
	// if (env)
	// 	free_env_list(env);
}

// void	free_env(t_env **env)
// {
// 	t_env	*curr;
// 	t_env	*next;

// 	if (env == NULL || (*env) == NULL)
// 		return ;
// 	curr = *env;
// 	while (curr)
// 	{
// 		next = curr->next;
// 		if (curr->name)
// 			free(curr->name);
// 		if (curr->value)
// 			free(curr->value);
// 		if (curr)
// 			free(curr);
// 		curr = next;
// 	}
// 	*env = NULL;
// }
