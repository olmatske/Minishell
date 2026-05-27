/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:09:53 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/27 21:18:32 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// cat < file.txt outputs file content to shell
static int	input(int fd)
{
	if (fd < 0)
		return (1);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (1);
	close(fd);
	return (0);
}

static int	overwrite(int fd)
{
	if (fd < 0)
		return (1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (1);
	close(fd);
	return (0);
}

static int	append(int fd)
{
	if (fd < 0)
		return (1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (1);
	close(fd);
	return (0);
}

int	wrapper_redirections(t_redir *redir)
{
	// printf("infile: %s\noutfile: %s\n", redir->infile, redir->outfile);
	int	status;

	if (!redir)
		return (0);
	status = 0;
	while (redir)
	{
		if (redir->infile)
			status = input(open(redir->infile, O_RDONLY));
		else if (redir->outfile && redir->out_type == OUT_OVERWRITE)
			status = overwrite(open(redir->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644));
		else if (redir->outfile && redir->out_type == OUT_APPEND)
			status = append(open(redir->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644));
		if (status != 0 && redir->infile)
			return (fprintf(stderr, "%s %s: %s\n", M, redir->infile, strerror(errno)), 1);
		else if (status != 0 && redir->out_type)
			return (fprintf(stderr, "%s %s: %s\n", M, redir->outfile, strerror(errno)), 1);
		if (status != 0)
			return (1);
		redir = redir->next;

	}
	return (status);
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

