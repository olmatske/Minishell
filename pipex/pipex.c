/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:59:21 by anshuval          #+#    #+#             */
/*   Updated: 2026/01/22 16:04:57 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	close_and_wait_status(pid_t pid1, pid_t pid2, int pipe_fd[2])
{
	int	status;

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fd[2];

	validate(argc);
	if (pipe(pipe_fd) == -1)
		ft_perror("pipe");
	pid1 = fork();
	if (pid1 == -1)
		ft_perror("fork");
	if (pid1 == 0)
	{
		close(pipe_fd[0]);
		child_process_cmd1(argv[2], argv[1], envp, pipe_fd);
	}
	pid2 = fork();
	if (pid2 == -1)
		ft_perror("fork");
	if (pid2 == 0)
	{
		close(pipe_fd[1]);
		child_process_cmd2(argv[3], argv[4], envp, pipe_fd);
	}
	return (close_and_wait_status(pid1, pid2, pipe_fd));
}
