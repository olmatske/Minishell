/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:41:47 by olmatske          #+#    #+#             */
/*   Updated: 2026/06/04 17:24:26 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	handle_abortion(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("^\\Quit (core dumped)", STDERR_FILENO);
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
		fprintf(stderr, C_RED"%s: Is a directory\n", path);
		return (free_split(arr), exit(126));
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, cmd->args, arr);
	saved_errno = errno;
	fprintf(stderr, C_RED"%s %s: %s\n", M, path, strerror(saved_errno));
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
		return (fprintf(stderr, C_RED"%s malloc failure\n", M), 1);
	if (decide_path(cmd))
		path = cmd->args[0];
	else
		path = resolve_path(shell, cmd, arr);
	if (!path)
		return (free_split(arr),
			fprintf(stderr, C_RED"%s: %s", cmd->args[0], C), 127);
	pid = fork();
	if (pid < 0)
		return (free_split(arr), fprintf(stderr, C_RED"%s fork failure\n", M), 1);
	if (pid == 0)
		child_exec(cmd, path, arr);
	waitpid(pid, &status, 0);
	free_split(arr);
	return (handle_abortion(status));
}
