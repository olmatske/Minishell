/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:52:47 by anshuval          #+#    #+#             */
/*   Updated: 2026/03/22 20:16:19 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

int	check_quotes(char *line)
{
	int	inside_single_quotes;
	int	inside_double_quotes;
	int	i;

	inside_single_quotes = NO;
	inside_double_quotes = NO;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' && inside_single_quotes == NO)
			inside_double_quotes = !inside_double_quotes;
		else if (line[i] == '\'' && inside_double_quotes == NO)
			inside_single_quotes = !inside_single_quotes;
		i++;
	}
	if (inside_double_quotes == YES || inside_single_quotes == YES)
	{
		printf("Syntax error. unclosed quotes.");
		return (NO);
	}
	return (YES);
}
