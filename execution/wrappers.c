/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 09:46:43 by olmatske          #+#    #+#             */
/*   Updated: 2026/06/04 16:47:05 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static	int	wrapper_export(t_shell *shell, t_env **env, t_cmd *cmd)
{
	char	**split;
	int		exit;

	exit = 0;
	if (!cmd->args[1])
		return (print_export(env_array_for_export(*env)), 0);
	split = ft_split(cmd->args[1], '=');
	if (!split || !split[0])
	{
		free_split(split);
		return (fprintf(stderr, C_RED"%s %s\n", M, I), 1);
	}
	exit = export(shell, env, cmd->args[1], split);
	free_split(split);
	return (exit);
}

int	wrapper_builtins(t_shell *shell, t_cmd_node *cmd_node, t_env **env)
{
	int		exit;

	exit = 0;
	if (cmd_node->cmd->built_in_name == BUILTIN_NONE)
		return (0);
	else if (cmd_node->cmd->built_in_name == BUILTIN_ECHO)
		exit = echo(cmd_node->cmd->args);
	else if (cmd_node->cmd->built_in_name == BUILTIN_PWD)
		exit = pwd();
	else if (cmd_node->cmd->built_in_name == BUILTIN_EXIT)
		exit = ft_exit(shell, env, cmd_node);
	else if (cmd_node->cmd->built_in_name == BUILTIN_ENV)
		exit = ft_env(env);
	else if (cmd_node->cmd->built_in_name == BUILTIN_CD)
		exit = cd(cmd_node->cmd->args, *env, shell);
	else if (cmd_node->cmd->built_in_name == BUILTIN_EXPORT)
		exit = wrapper_export(shell, env, cmd_node->cmd);
	else if (cmd_node->cmd->built_in_name == BUILTIN_UNSET)
		exit = unset(env, cmd_node->cmd->args[1]);
	return (exit);
}

int	wrapper_all(t_shell *shell, t_cmd_node *n, t_env **env, int exit)
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
