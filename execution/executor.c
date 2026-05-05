/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:39:56 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/05 14:50:36 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_pipeline(t_shell *shell, t_cmd_node *cmd_list, int cmd_count)
{
	pid_t		*pids;
	t_cmd_node	*curr;
	int			pipe_fd[2]; // pipe_fd[0] read - pipde_fd[1] write
	int			prev_read;
	int			i;

	i = 0;
	prev_read = -1;
	pids = gc_malloc(shell, sizeof(pid_t) * cmd_count);
	curr = cmd_list;
	while (i < cmd_count)
	{
		if (i < cmd_count - 1 && pipe(pipe_fd) == - 1) // new pipe if not last command
			return (perror("pipes"), 1);
		pids[i] = fork();
		if (pids[i] == -1)
			return (perror("fork"), 1);
		// if (extra(i, cmd_count, &pipe_fd, pids[i]) == 1)
		// 	exit(127);
		if (pids[i] == 0) // child proccess
		{
			child_loop(i, cmd_count, &pipe_fd, prev_read);
			execution(curr->cmd, shell->env); 
			exit(127);
		}
		else
			parent_loop(i, cmd_count, *pipe_fd, prev_read);
		curr = curr->next;
		i++;
	}
}

static int	extra(int i, int cmd_count, int *pipe_fd, int *pids)
{
	if (i < cmd_count - 1 && pipe(pipe_fd) == - 1) // new pipe if not last command
			return (perror("pipes"), 1);
		pids[i] = fork();
	if (pids[i] == -1)
		return (perror("fork"), 1);
}

static void	child_loop(int i, int cmd_count, int *pipe_fd, int prev_read)
{
	if (prev_read != -1)
		redirect_input(prev_read);
	if (i < cmd_count - 1)
		redirect_output(pipe_fd[1]);
	if (i < cmd_count - 1)
		close(pipe_fd[0]);
}

static void	parent_loop(int i, int cmd_count, int *pipe_fd, int prev_read)
{
	if (i < cmd_count - 1)
		close(pipe_fd[1]);
	if (prev_read != -1)
		close(prev_read);
	if (i < cmd_count - 1)
		prev_read = pipe_fd[0];
	else
		prev_read = -1;
}
