/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:23:33 by anshuval          #+#    #+#             */
/*   Updated: 2026/04/14 13:39:40 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

void	check_for_builtin(t_cmd_node *node)
{
	if (node->cmd->args == NULL || node->cmd->args[0] == NULL)
		return ;
	if (ft_strncmp(node->cmd->args[0], "echo", 5) == 0)
		node->cmd->built_in_name = BUILTIN_ECHO;
	else if (ft_strncmp(node->cmd->args[0], "cd", 3) == 0)
		node->cmd->built_in_name = BUILTIN_CD;
	else if (ft_strncmp(node->cmd->args[0], "pwd", 4) == 0)
		node->cmd->built_in_name = BUILTIN_PWD;
	else if (ft_strncmp(node->cmd->args[0], "export", 7) == 0)
		node->cmd->built_in_name = BUILTIN_EXPORT;
	else if (ft_strncmp(node->cmd->args[0], "unset", 6) == 0)
		node->cmd->built_in_name = BUILTIN_UNSET;
	else if (ft_strncmp(node->cmd->args[0], "env", 4) == 0)
		node->cmd->built_in_name = BUILTIN_ENV;
	else if (ft_strncmp(node->cmd->args[0], "exit", 5) == 0)
		node->cmd->built_in_name = BUILTIN_EXIT;
}
