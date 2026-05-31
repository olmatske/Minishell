/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:32:58 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/31 20:40:11 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_delimiter_quote_status(t_token *token_list, char *delimiter)
{
	while (token_list)
	{
		if (token_list->type == WORD && token_list->value != NULL
			&& ft_strncmp(token_list->value, delimiter,
				(ft_strlen(delimiter) + 1)) == 0)
			return (token_list->was_quoted);
		token_list = token_list->next;
	}
	return (NO);
}

void	print_eof_warning(char *delimiter)
{
	ft_putstr_fd("Minishell: warning: here-document ", STDERR_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted '", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
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
