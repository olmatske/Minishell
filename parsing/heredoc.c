/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 16:36:57 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/29 22:55:16 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

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

static char	*write_to_tmp_file(char *heredoc, int counter)
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

char	*append_new_line(char *line, char *new_chunk)
{
	char	*tmp;

	tmp = append_str(line, new_chunk);
	free(new_chunk);
	if (tmp == NULL)
		return (NULL);
	line = append_str(tmp, "\n");
	return (line);
}

static char	*expand_line(char *line, t_env *env)
{
	int		i;
	char	*expanded;

	i = 0;
	expanded = NULL;
	while (line[i])
	{
		if (line[i] == '$')
			expand_env(line, &i, &expanded, env);
		else
			just_copy(line, &i, &expanded);
	}
	free(line);
	return (expanded);
}

char	*heredoc(char *delimiter, int counter, t_env *env)
{
	char	*heredoc;
	char	*line;

	heredoc = NULL;
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (g_signal == 130)
			return (free(line), free(heredoc), NULL);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, delimiter, (ft_strlen(delimiter) + 1)) == 0)
		{
			free (line);
			break ;
		}
		line = expand_line(line, env);
		if (line == NULL)
			return (free(heredoc), NULL);
		heredoc = append_new_line(heredoc, line);
		if (heredoc == NULL)
			return (NULL);
	}
	return (write_to_tmp_file(heredoc, counter));
}
