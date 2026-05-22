/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:57:42 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/22 15:04:10 by olmatske         ###   ########.fr       */
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

int	exec_single_cmd(t_shell *shell, t_env *env, t_cmd_node *cmd_list)
{
	if (cmd_list->cmd->built_in_name == BUILTIN_NONE)
		return (exec_external(shell, cmd_list->cmd, env));
	update_shell_status(shell->env, shell);
	return (wrapper_builtin(shell, cmd_list, shell->env));
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


