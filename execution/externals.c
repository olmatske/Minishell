/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:41:47 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/10 13:02:25 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// Absolute path: /bin/ls, /usr/bin/env. Starts with /; execute directly.

// Relative path: ./a.out, ../prog, dir/tool. Contains /; execute directly.

// Bare command: ls, cat, grep. Contains no /; search PATH


static int	decide_path(t_cmd cmd);
static char *resolve_path(t_cmd *cmd, t_env *env);

int exec_external(t_cmd *cmd, t_env *env)
{
	char	*path;
	// char	*str[] = {"./hi.sh", NULL};
	char	*str[] = {"ls", NULL};
	int		id;

	cmd->args = str;
	cmd->built_in_name = BUILTIN_UNSET;
	id = 0;

	if (decide_path(*cmd) == 1)
	{
		if (access(cmd->args[0], X_OK) != 0)
			return(perror("access"), 1);
		id = fork();
		if (id < 0)
			return(perror("fork"), 1);
		if (id == 0)
		{
			// execve(cmd->args[0], cmd->args, env);
			perror("execve");
		}
	}
	else
	{
		path = resolve_path(cmd, env);
		if (!path)
			return(perror("no path like that"), 1);
		// execve(path, cmd->args, env);
	}
	return (0);
}

static int	decide_path(t_cmd cmd)
{
	// int	pid;
	// char *path;

	// pid = 0;
	if (cmd.args[0][0] == '/' || (cmd.args[0][0] == '.' && cmd.args[0][1] == '/'))
		return (1);
	else
		return (2);
	// path = ft_strchr(cmd.args[0], '/');
	// printf("Path: %s\n", path);
	// return (3);
}


static char *resolve_path(t_cmd *cmd, t_env *env)
{
	(void)cmd;
	(void)env;
	// int	i;
	// char *path;

	// i = 0;
	// while (env[i])
	// {
	// 	path = ft_strnstr(env[i], ":", ft_strlen(envp[i]));
	// 	printf("%d: %s\n", i, path);
	// 	path = ft_strjoin(path, cmd->args[0]);
	// 	if (access(path, X_OK) != 0)
	// 	{
	// 		free(path);
	// 		i++;
	// 	}
	// 	else
	// 		return (printf("Found path: %s\n", path), path);

	// }
	return (NULL);
}



// Resolve the path.

// Check it with access(path, X_OK) or access(path, F_OK) depending on what you want to know.

// If it passes, fork().

// In the child, call execve().

// In the parent, waitpid().