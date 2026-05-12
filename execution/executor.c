/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:39:56 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/12 14:28:58 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static t_pipex	*pipex_init(t_shell *shell, t_cmd_node *cmd_list)
{
	t_pipex	*p;

	p = gc_malloc(shell, sizeof(t_pipex));
	p->curr = cmd_list;
	p->shell = shell;
	p->cmd_count = pipe_count(cmd_list);
	p->pids = gc_malloc(shell, sizeof(pid_t) * p->cmd_count);
	p->pipe_fd[0] = -1;
	p->pipe_fd[1] = -1;
	p->i = 0;
	p->prev_read = -1;
	return (p);
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

static void	parent_loop(int i, int cmd_count, int *pipe_fd, int *prev_read)
{
	if (i < cmd_count - 1)
		close(pipe_fd[1]);
	if (*prev_read != -1)
		close(*prev_read);
	if (i < cmd_count - 1)
		*prev_read = pipe_fd[0];
	else
		*prev_read = -1;
}
	
static int	pipe_loop(t_pipex *p)
{
	if (p->i < p->cmd_count - 1 && pipe(p->pipe_fd) == -1)
		return (perror("pipes"), 1);
	p->pids[p->i] = fork();
	if (p->pids[p->i] == -1)
		return (perror("fork"), 1);
	if (p->pids[p->i] == 0)
	{
		child_loop(p->i, p->cmd_count, p->pipe_fd, p->prev_read);
		execution(p->curr->cmd, env_for_execution(p->shell->env));
		exit(1);
	}
	else
		parent_loop(p->i, p->cmd_count, p->pipe_fd, &p->prev_read);
	return (0);
}

int	exec_pipeline(t_shell *shell, t_cmd_node *cmd_list)
{
	t_pipex	*p;
	int		status;

	p = pipex_init(shell, cmd_list);
	while (p->i < p->cmd_count)
	{
		if (pipe_loop(p) == 1)
			return (1);
		p->curr = p->curr->next;
		p->i++;
	}
	p->i = 0;
	while (p->i < p->cmd_count)
	{
		waitpid(p->pids[p->i], &status, 0);
		p->i++;
	}
	return (0);
}

