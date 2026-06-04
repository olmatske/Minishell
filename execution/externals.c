/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:41:47 by olmatske          #+#    #+#             */
/*   Updated: 2026/06/04 21:34:43 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	handle_abortion(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd(C_RED"Quit (core dumped)"R, STDERR_FILENO);
		else if (WTERMSIG(status) == SIGINT)
			ft_putchar_fd('\n', STDERR_FILENO);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

static void	child_exec(t_cmd *cmd, char *path, char **arr)
{
	int			saved_errno;
	struct stat	st;

	if (cmd->redir && wrapper_redirections(cmd->redir) != 0)
		return (free_split(arr), exit(1));
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		fprintf(stderr, C_RED"%s: Is a directory\n"R, path);
		return (free_split(arr), exit(126));
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, cmd->args, arr);
	saved_errno = errno;
	fprintf(stderr, C_RED"%s %s: %s\n"R, M, path, strerror(saved_errno));
	free_split(arr);
	if (saved_errno == EACCES || saved_errno == EISDIR)
		exit(126);
	exit(127);
}

int	exec_external(t_shell *shell, t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**arr;
	int		pid;
	int		status;

	arr = env_array_for_execution(env);
	if (!arr)
		return (fprintf(stderr, C_RED"%s malloc failure\n"R, M), 1);
	path = cmd->args[0];
	if (!decide_path(cmd))
		path = resolve_path(shell, cmd, arr);
	if (!path)
		return (free_split(arr),
			fprintf(stderr, C_RED"%s: %s"R, cmd->args[0], C), 127);
	pid = fork();
	if (pid < 0)
		return (free_split(arr), fprintf(stderr, C_RED"%s %s\n"R, M, F), 1);
	if (pid == 0)
		child_exec(cmd, path, arr);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	replace_signals();
	free_split(arr);
	return (handle_abortion(status));
}
