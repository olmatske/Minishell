/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:00:06 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/27 13:16:09 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execution(char *cmd, char **envp)
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
	command_path = find_command_path(command[0], envp);
	if (command_path == NULL)
	{
		ft_free_array(command);
		ft_error("Command not found", 127);
	}
	execve(command_path, command, envp);
	perror(command[0]);
	ft_free_array(command);
	free(command_path);
	exit(126);
}

static int	open_file(char *file, int mode)
{
	int	fd;

	fd = -1;
	if (mode == 0)
		fd = open(file, O_RDONLY);
	else if (mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(file);
		exit(1);
	}
	return (fd);
}

void	child_process_cmd1(char *cmd, char *file, char **envp, int pipe_fd[2])
{
	int		in_file;

	in_file = open_file(file, 0);
	if (dup2(in_file, STDIN_FILENO) == -1)
		ft_perror ("dup2");
	close(in_file);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		ft_perror("dup2");
	close(pipe_fd[1]);
	execution(cmd, envp);
}

void	child_process_cmd2(char *cmd, char *file, char **envp, int pipe_fd[2])
{
	int		out_file;

	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		ft_perror ("dup2");
	out_file = open_file(file, 1);
	if (dup2(out_file, STDOUT_FILENO) == -1)
		ft_perror ("dup2");
	close (out_file);
	close(pipe_fd[0]);
	execution(cmd, envp);
}
