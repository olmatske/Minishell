/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:57:42 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/12 14:32:34 by olmatske         ###   ########.fr       */
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
	return (exec_single_cmd(shell, *shell->env, cmd_list));
}

// add shell struct

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
	if (shell)
		gc_free_all(shell);
	if (shell)
		free(shell);
	if (env)
		*env = NULL;
}

// execution(p->curr->cmd, p->shell->env)
void	execution(t_cmd *cmd, char **env)
{
	char	*command_path;
	char	**command;

	command = ft_split(cmd, ' ');
	if (command == NULL)
		ft_perror("command");
	if (command[0] == NULL)
	{
		ft_free_array(command);
		ft_error("Command not found", 127);
	}
	command_path = find_command_path(command[0], env);
	if (command_path == NULL)
	{
		ft_free_array(command);
		ft_error("Command not found", 127);
	}
	execve(command_path, command, env);
	perror(command[0]);
	ft_free_array(command);
	free(command_path);
	exit(126);
}
