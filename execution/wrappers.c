/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 09:46:43 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/29 10:30:29 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static	int	wrapper_export(t_shell *shell, t_env **env, t_cmd *cmd)
{
	char	**split;
	int		exit;

	exit = 0;
	if (!cmd->args[1])
		return (print_export(env_array_for_execution(*env)), 0);
	split = ft_split(cmd->args[1], '=');
	if (!split || !split[0])
	{
		free_split(split);
		return (fprintf(stderr, "%s %s\n", M, I), 1);

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
