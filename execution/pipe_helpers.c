/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:24:58 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/16 13:06:09 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	open_file(char *file, int mode)
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

int	pipe_count(t_cmd_node *cmd_list)
{
	t_cmd_node	*curr;
	int	i;
	
	curr = cmd_list;
	i = 0;
	if (curr->next)
	{
		i = 1;
		while (curr->next != NULL)
		{
			curr = curr->next;
			i++;
		}
	}
	return (i);
}
void	redirect_input(int fd)
{
	if (fd != -1)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		perror("dup2 stdin");
		close(fd);
	}
}

void	redirect_output(int fd)
{
	if (fd != -1)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		perror("dup2 stdout");
		close(fd);
	}
}

void	execution(t_shell *shell, t_cmd_node *cmd, t_env **env)
{
	if (cmd->cmd->built_in_name == BUILTIN_NONE)
		exec_external(cmd->cmd, *env);
	else
		wrapper_builtin(shell, cmd, env);
}
