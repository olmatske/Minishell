/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:52:47 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/11 15:59:52 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

int	quote_status(char c, int *in_double, int *in_single)
{
	if (c == '\"' && *in_single == NO)
	{
		*in_double = !(*in_double);
			return (YES);
	}
	else if (c == '\'' && *in_double == NO)
	{
		*in_single = !(*in_single);
			return (YES);
	}
	return (NO);
}

static int	has_unclosed_quotes(char *line)
{
	int		in_single;
	int		in_double;
	int		i;

	in_single = NO;
	in_double = NO;
	i = 0;
	while (line && line[i])
	{
		quote_status(line[i], &in_double, &in_single);
		i++;
	}
	if (in_double == YES || in_single == YES)
		return (YES);
	return (NO);
}

char	*read_full_command(char *line)
{

	char	*tmp;
	char	*next;

	tmp = NULL;
	next = NULL;
	while (has_unclosed_quotes(line) == YES)
	{
		next = readline("> ");
		if (next == NULL)
			return (free(line), NULL);
		tmp = append_str(line, "\n");
		if (tmp == NULL)
			return (free(line), free(next), NULL);
		free(line);
		line = ft_strjoin(tmp, next);
		if (line == NULL)
			return (free(tmp), free(next), NULL);
		free(next);
		free(tmp);
	}
	return (line);
}

int	check_quotes(char *line)
{
	if (has_unclosed_quotes(line) == YES)
	{
		while (has_unclosed_quotes(line) == YES)
			line = read_full_command(line);
	}
	return (YES);
}

int	is_it_space_only(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != 32 && (line[i] < 9 || line[i] > 13))
			return (0);
		i++;
	}
	return (1);
}
