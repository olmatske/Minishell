/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:39:56 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/30 22:44:02 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	child_loop(int i, int cmd_count, int *pipe_fd, int prev_read)
{
	if (prev_read != -1)
		redirect_input(prev_read);
	if (i < cmd_count - 1)
		redirect_output(pipe_fd[1]);
	if (i < cmd_count - 1)
		close(pipe_fd[0]);
}

void	parent_loop(int i, int cmd_count, int *pipe_fd, int *prev_read)
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

int	pipe_loop(t_pipex *p)
{
	if (p->i < p->cmd_count - 1 && pipe(p->pipe_fd) == -1)
		return (perror("pipes"), 1);
	p->pids[p->i] = fork();
	if (p->pids[p->i] == -1)
		return (perror("fork"), 1);
	if (p->pids[p->i] == 0)
	{
		child_loop(p->i, p->cmd_count, p->pipe_fd, p->prev_read);
		if (p->curr->cmd->redir
			&& wrapper_redirections(p->curr->cmd->redir) != 0)
			exit (1);
		if (p->curr->cmd->redir
			&& wrapper_redirections(p->curr->cmd->redir) != 0)
			exit(1);
		exit(execution(p->shell, p->curr, p->shell->env));
	}
	else
		parent_loop(p->i, p->cmd_count, p->pipe_fd, &p->prev_read);
	return (0);
}

// int	pipe_loop(t_pipex *p)
// {
// 	if (p->i < p->cmd_count - 1 && pipe(p->pipe_fd) == -1)
// 		return (perror("pipes"), 1);
// 	p->pids[p->i] = fork();
// 	if (p->pids[p->i] == -1)
// 		return (perror("fork"), 1);
// 	if (p->pids[p->i] == 0)
// 	{
// 		if (p->curr->cmd->redir
// 			&& wrapper_redirections(p->curr->cmd->redir) != 0)
// 			exit (1);
// 		child_loop(p->i, p->cmd_count, p->pipe_fd, p->prev_read);
// 		if (p->curr->cmd->redir
// 			&& wrapper_redirections(p->curr->cmd->redir) != 0)
// 			exit(1);
// 		exit(execution(p->shell, p->curr, p->shell->env));
// 	}
// 	else
// 		parent_loop(p->i, p->cmd_count, p->pipe_fd, &p->prev_read);
// 	return (0);
// }

int	wait_pipeline(t_shell *shell, t_pipex *p)
{
	int	status;
	int	last_status;

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
	return (update_shell_status(shell->env, shell), 0);
}

int	exec_pipeline(t_shell *shell, t_cmd_node *cmd_list)
{
	t_pipex	*p;

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
	return (wait_pipeline(shell, p));
}
