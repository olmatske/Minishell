/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 16:36:57 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/31 23:47:48 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_interrupted(char *line, char **heredoc, char *delimiter)
{
	if (g_signal == 130 || line == NULL)
	{
		free(line);
		if (g_signal == 130)
		{
			free(*heredoc);
			*heredoc = NULL;
		}
		else
			print_eof_warning(delimiter);
		return (YES);
	}
	if (ft_strncmp(line, delimiter, (ft_strlen(delimiter) + 1)) == 0)
	{
		free (line);
		return (YES);
	}
	return (NO);
}

static char	*expand_line(char *line, t_env *env)
{
	int		i;
	char	*expanded;

	i = 0;
	expanded = NULL;
	while (line[i])
		search_dollar_or_copy(line, &i, &expanded, env);
	free(line);
	if (expanded == NULL)
		return (ft_strdup(""));
	return (expanded);
}

static int	heredoc_loop(char **heredoc, char *delimiter, int was_quoted,
		t_env *env)
{
	char	*line;

	line = readline("> ");
	if (is_interrupted(line, heredoc, delimiter) == YES)
		return (NO);
	if (was_quoted == NO)
		line = expand_line(line, env);
	if (line == NULL)
	{
		free(*heredoc);
		*heredoc = NULL;
		return (NO);
	}
	*heredoc = join_prefix(*heredoc, line, "\n");
	free(line);
	if (*heredoc == NULL)
		return (NO);
	return (YES);
}

static char	*read_from_heredoc(char *delimiter, int was_quoted, t_env *env)
{
	char	*heredoc;
	int		copy_stdin;

	heredoc = NULL;
	copy_stdin = start_interrupt_prompt();
	while (1)
	{
		if (heredoc_loop(&heredoc, delimiter, was_quoted, env) == NO)
			break ;
	}
	end_interrupt_prompt(copy_stdin);
	return (heredoc);
}

char	*heredoc(char *delimiter, int was_quoted, int counter, t_env *env)
{
	char	*heredoc;
	char	*filename;

	heredoc = NULL;
	filename = NULL;
	heredoc = read_from_heredoc(delimiter, was_quoted, env);
	if (heredoc == NULL && g_signal == 130)
		return (NULL);
	filename = write_to_tmp_file(heredoc, counter);
	return (filename);
}
