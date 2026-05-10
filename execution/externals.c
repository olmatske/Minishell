/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:41:47 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/10 17:59:10 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// Absolute path: /bin/ls, /usr/bin/env. Starts with /; execute directly.

// Relative path: ./a.out, ../prog, dir/tool. Contains /; execute directly.

// Bare command: ls, cat, grep. Contains no /; search PATH


static int	decide_path(t_cmd cmd);
static char *resolve_path(t_cmd *cmd, char **env);

int exec_external(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**env_array;
	int		pid;
	int		status;

	env_array = env_array_for_execution(env);
	path = NULL;
	if (decide_path(*cmd) == 1)
		path = cmd->args[0];
	else
		path = resolve_path(cmd, env_array);
	if (!path)
		return (perror("command not found"), 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		execve(path, cmd->args, env_array);
		perror("execve");
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (0);
}

static int	decide_path(t_cmd cmd)
{
	if (cmd.args[0][0] == '/' || (cmd.args[0][0] == '.' && cmd.args[0][1] == '/'))
		return (1);
	else
		return (2);
}


static char *resolve_path(t_cmd *cmd, char **env)
{
	(void)cmd;
	(void)env;
	int	i;
	char *path;

	i = 0;
	while (env[i])
	{
		path = ft_strnstr(env[i], ":", ft_strlen(env[i]));
		printf("%d: %s\n", i, path);
		path = ft_strjoin(path, cmd->args[0]);
		if (access(path, X_OK) != 0)
		{
			free(path);
			i++;
		}
		else
			return (printf("Found path: %s\n", path), path);
	}
	return (NULL);
}



// Resolve the path.

// Check it with access(path, X_OK) or access(path, F_OK) depending on what you want to know.

// If it passes, fork().

// In the child, call execve().

// In the parent, waitpid().