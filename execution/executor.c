/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:39:56 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/04 17:00:22 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	exec_pipeline(t_shell *shell, t_cmd_node *cmd_list, int cmd_count)
{
	pid_t		*pids;
	t_cmd_node	*curr;
	int			pipe_fd[2];
	int			prev_read;
	int			i;

	i = 0;
	prev_read = -1;
	pids = gc_malloc(shell, sizeof(pid_t) * cmd_count);
	while (i < cmd_count)
	{
		if (i < cmd_count - 1 && pipe(pipe_fd) == - 1)
			return (perror("pipes"), 1);
		pids[i] = fork();
		if (pids[i] == -1)
			return (perror("fork"), 1);
		if (pids[i] == 0)
			
	}
}

int	pipe_count(t_cmd_node *cmd_list)
{
	t_cmd_node	*curr;
	int	i;
	
	curr = cmd_list;
	i = 0;
	if (curr->next)
	{
		i = 1;
		while (curr->next != NULL)
		{
			curr = curr->next;
			i++;
		}
	}
	return (i);
}
	int	exec_single_cmd(t_env *environment, t_cmd_node *cmd_list)
	{
		if (cmd_list->cmd->builtin == NONE_B)
			return (exec_external(env, cmd_list->cmd));
		return (wrapper_builtin(cmd_list->cmd, environment));
	}
