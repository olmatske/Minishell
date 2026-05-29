/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:33:53 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/29 11:47:34 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	decide_path(t_cmd *cmd)
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

char	*join_path(t_shell *shell, char *dir, char *cmd)
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

char	*resolve_path(t_shell *shell, t_cmd *cmd, char **env)
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
