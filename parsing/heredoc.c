/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 16:36:57 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/30 23:02:05 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

static char	*append_new_line(char *line, char *new_chunk)
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

static int	check_line_status(char *delimiter, char *line)
{
	if (line == NULL)
	{
		print_eof_warning(delimiter);
		return (-1);
	}
	if (ft_strncmp(line, delimiter, (ft_strlen(delimiter) + 1)) == 0)
	{
		free (line);
		return (-1);
	}
	return (0);
}

static void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	g_signal = 130;
	write(1, "\n", 1);
	close(0);
}

static char	*read_from_heredoc(char *delimiter, t_env *env)
{
	char	*heredoc;
	char	*new_heredoc;
	char	*line;
	int		copy_stdin;

	heredoc = NULL;
	new_heredoc = NULL;
	line = NULL;
	copy_stdin = dup(0);
	signal(SIGINT, handle_heredoc_sigint);
	while (1)
	{
		line = readline("> ");
		if (g_signal == 130)
		{
			free(line);
			free(heredoc);
			heredoc = NULL;
			break ;
		}
		if (check_line_status(delimiter, line) == -1)
			break ;
		line = expand_line(line, env);
		if (line == NULL)
		{
			free(heredoc);
			heredoc = NULL;
			break ;
		}
		new_heredoc = append_new_line(heredoc, line);
		if (new_heredoc == NULL)
		{
			free(heredoc);
			heredoc = NULL;
			break ;
		}
		heredoc = new_heredoc;
	}
	replace_signals();
	if (copy_stdin >= 0)
	{
		dup2(copy_stdin, 0);
		close(copy_stdin);
	}
	return (heredoc);
}

char	*heredoc(char *delimiter, int counter, t_env *env)
{
	char	*heredoc;
	char	*filename;

	heredoc = NULL;
	filename = NULL;
	heredoc = read_from_heredoc(delimiter, env);
	if (heredoc == NULL && g_signal == 130)
		return (NULL);
	filename = write_to_tmp_file(heredoc, counter);
	return (filename);
}
