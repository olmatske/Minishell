/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:09:53 by olmatske          #+#    #+#             */
/*   Updated: 2026/06/05 14:22:49 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

int	wrapper_redirections(t_redir *r)
{
	int	s;

	if (!r)
		return (0);
	s = 0;
	while (r)
	{
		if (r->infile)
			s = input(open(r->infile, O_RDONLY));
		else if (r->outfile && r->out_type == OUT_OVERWRITE)
			s = overwrite(open(r->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644));
		else if (r->outfile && r->out_type == OUT_APPEND)
			s = append(open(r->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644));
		if (s != 0 && r->infile)
			return (ft_puterr(r->infile, strerror(errno), NULL), 1);
		else if (s != 0 && r->out_type)
			return (ft_puterr(r->outfile, strerror(errno), NULL), 1);
		if (s != 0)
			return (1);
		r = r->next;
	}
	return (s);
}
