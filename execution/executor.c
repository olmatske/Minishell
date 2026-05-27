/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:39:56 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/27 21:49:24 by olmatske         ###   ########.fr       */
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
		if (p->curr->cmd->redir && wrapper_redirections(p->curr->cmd->redir) != 0)
			exit (1);
		child_loop(p->i, p->cmd_count, p->pipe_fd, p->prev_read);
		if (p->curr->cmd->redir 
				&& wrapper_redirections(p->curr->cmd->redir) != 0)
			exit(1);
			// exec_external_child(p->shell, p->curr->cmd, *(p->shell->env));
		exit(execution(p->shell, p->curr, p->shell->env));
	}
	else
		parent_loop(p->i, p->cmd_count, p->pipe_fd, &p->prev_read);
	return (0);
}

int	exec_pipeline(t_shell *shell, t_cmd_node *cmd_list)
{
	t_pipex	*p;
	int		status;
	int		last_status;

	p = pipex_init(shell, cmd_list);
	if (!p)
		return (1);
	while (p->i < p->cmd_count)
	{
		if (pipe_loop(p) == 1)
			return (1);
		p->curr = p->curr->next;
		p->i++;
	}
	last_status = 0;
	p->i = 0;
	while (p->i < p->cmd_count)
	{
		if (waitpid(p->pids[p->i], &status, 0) == -1)
			return (perror("waitpid"), 1);
		if (p->i == p->cmd_count - 1)
			last_status = status;
		p->i++;
	}
	if (WIFEXITED(last_status))
		shell->exit = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status))
		shell->exit = 128 + WTERMSIG(last_status);
	else
		shell->exit = 1;
	update_shell_status(shell->env, shell);
	return (0);
}
