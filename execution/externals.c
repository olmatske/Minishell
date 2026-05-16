/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:41:47 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/16 14:55:25 by olmatske         ###   ########.fr       */
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

char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	if (!dir || dir[0] == '\0')
		return (ft_strjoin("./", cmd));
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
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

static char *resolve_path(t_cmd *cmd, char **env)
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
		full_path = join_path(paths[i], cmd->args[0]);
		if (full_path && access(full_path, X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

int	exec_external(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**env_array;
	int		pid;
	int		status;

	env_array = env_array_for_execution(env);
	path = NULL;
	if (decide_path(cmd))
		path = cmd->args[0];
	else
		path = resolve_path(cmd, env_array);
	if (!path)
		return (free_split(env_array), fprintf(stderr, "%s: %s", cmd->args[0], CNF), 1);
	pid = fork();
	if (pid < 0)
		return (free_split(env_array), fprintf(stderr, "fork\n"), 1);
	if (pid == 0)
	{
		execve(path, cmd->args, env_array);
		fprintf(stderr, "%s: %s\n", path, strerror(errno));
		if (errno == EACCES || errno == EISDIR)
			exit(126);
		else
			exit(127);
	}
	waitpid(pid, &status, 0);
	free_split(env_array);
	return (0);
}
