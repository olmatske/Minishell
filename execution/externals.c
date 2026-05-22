/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:41:47 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/22 14:50:36 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	decide_path(t_cmd *cmd)
{
	char	*arg;

	if (!cmd || !cmd->args)
		return (0);
	arg = cmd->args[0];
	if (!arg || arg[0] == '\0')
		return (0);
	return (ft_strchr(arg, '/') != NULL);
}

char	*get_path_value(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*join_path(t_shell *shell, char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	if (!dir || dir[0] == '\0')
		return (gc_strjoin(shell, "./", cmd));
	tmp = gc_strjoin(shell, dir, "/");
	if (!tmp)
		return (NULL);
	full = gc_strjoin(shell, tmp, cmd);
	return (full);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static char *resolve_path(t_shell *shell, t_cmd *cmd, char **env)
{
	char	*path_value;
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	path_value = get_path_value(env);
	if (!path_value || !cmd || !cmd->args || !cmd->args[0])
		return (NULL);
	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_path = join_path(shell, paths[i], cmd->args[0]);
		if (full_path && access(full_path, X_OK) == 0)
			return (free_split(paths), full_path);
		gc_single_free(shell, full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

int	exec_external(t_shell *shell, t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**arr;
	int		pid;
	int		status;
	int		mpath;

	arr = env_array_for_execution(env);
	if (!arr)
		return (fprintf(stderr, "malloc failure/n"), 1);
	path = NULL;
	mpath = 0;
	if (decide_path(cmd))
		path = cmd->args[0];
	else
	{
		path = resolve_path(shell, cmd, arr);
		mpath = 1;
	}
	if (!path)
		return (free_split(arr), fprintf(stderr, "%s: %s", cmd->args[0], C), 1);
	pid = fork();
	if (pid < 0)
	{
		if (mpath)
			free(path);
		return (free_split(arr), fprintf(stderr, "fork\n"), 1);
	}
	if (pid == 0)
	{
		execve(path, cmd->args, arr);
		fprintf(stderr, "%s: %s\n", path, strerror(errno));
		if (errno == EACCES || errno == EISDIR)
			exit(126);
		else
			exit(127);
	}
	waitpid(pid, &status, 0);
	if (mpath)
		free(path);
	free_split(arr);
	return (0);
}
