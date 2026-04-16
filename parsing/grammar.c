/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:52:47 by anshuval          #+#    #+#             */
/*   Updated: 2026/04/16 15:15:52 by anshuval         ###   ########.fr       */
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

int	check_quotes(char *line)
{
	int	in_single;
	int	in_double;
	int	i;

	in_single = NO;
	in_double = NO;
	i = 0;
	while (line[i])
	{
		quote_status(line[i], &in_double, &in_single);
		i++;
	}
	if (in_double == YES || in_single == YES)
	{
		printf("Syntax error. Unclosed quotes.");
		return (NO);
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
