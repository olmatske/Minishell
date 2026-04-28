/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:01:53 by anshuval          #+#    #+#             */
/*   Updated: 2026/01/22 16:38:11 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*create_full_path(char *directory, char *command)
{
	char	*full_path;
	char	*path_build;

	path_build = ft_strjoin(directory, "/");
	if (path_build == NULL)
		return (NULL);
	full_path = ft_strjoin(path_build, command);
	if (full_path == NULL)
	{
		free(path_build);
		return (NULL);
	}
	free(path_build);
	return (full_path);
}

static char	*search_in_directories(char **directory, char *command)
{
	char	*full_path;
	int		i;

	i = 0;
	while (directory[i])
	{
		full_path = create_full_path(directory[i], command);
		if (full_path == NULL)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *command, char **envp)
{
	char	*full_path;
	char	**directory;

	if (ft_strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
	}
	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (*envp == NULL)
		return (NULL);
	directory = ft_split(*envp + 5, ':');
	if (directory == NULL)
		return (NULL);
	full_path = search_in_directories(directory, command);
	if (full_path == NULL)
	{
		ft_free_array(directory);
		return (NULL);
	}
	ft_free_array(directory);
	return (full_path);
}

void	validate(int argc)
{
	if (argc != 5)
		ft_error("Input exactly four arguments", 2);
}
