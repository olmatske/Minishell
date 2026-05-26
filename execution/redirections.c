/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:09:53 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/26 10:33:19 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// cat < file.txt outputs file content to shell
static int	input(int fd)
{
	if (fd < 0)
		return (perror("infile fd:"), 1);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (perror("infile dup2:"), 1);
	close(fd);
	return (0);
}

static int	overwrite(int fd)
{
	if (fd < 0)
		return (perror("overwrite fd:"), 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (perror("overwrite dup2:"), 1);
	close(fd);
	return (0);
}

static int	append(int fd)
{
	if (fd < 0)
		return (perror("append fd:"), 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (perror("append dup2:"), 1);
	close(fd);
	return (0);
}

int	wrapper_redirections(t_redir *redir)
{
	int	exit;

	if (!redir)
		return (0);
	exit = 0;
	if (redir->infile)
		exit = input(open(redir->infile, O_RDONLY));
	if (redir->outfile && redir->out_type == OUT_OVERWRITE)
		exit = overwrite(open(redir->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->outfile && redir->out_type == OUT_APPEND)
		exit = append(open(redir->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (exit);
}

// int create_file(char *filename)
// {
// 	int		fd;
	
// 	fd = open(filename, O_CREAT | O_RDWR, 0644);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	if (close(fd) < 0)
// 	{
// 		perror("close");
// 		return (1);
// 	}
// 	return (0);
// }

