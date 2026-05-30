/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:32:58 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/30 20:06:12 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

void	print_eof_warning(char *delimiter)
{
	ft_putstr_fd("Minishell: warning: here-document delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted '", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

static char	*create_filename(int counter)
{
	char	*counter_str;
	char	*filename;

	counter_str = ft_itoa(counter);
	if (counter_str == NULL)
		return (NULL);
	filename = ft_strjoin(".heredoc_tmp_", counter_str);
	free(counter_str);
	if (filename == NULL)
		return (NULL);
	return (filename);
}

char	*write_to_tmp_file(char *heredoc, int counter)
{
	char	*filename;
	int		fd;

	filename = create_filename(counter);
	if (filename == NULL)
		return (free(heredoc), NULL);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (free(heredoc), free(filename), NULL);
	if (heredoc)
	{
		ft_putstr_fd(heredoc, fd);
		free(heredoc);
	}
	close(fd);
	return (filename);
}
