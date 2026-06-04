/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 18:50:43 by anshuval          #+#    #+#             */
/*   Updated: 2026/06/04 17:53:33 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// check for all the redirection signs in one place. according to the bash 
// syntax the signs have to be followed by a word (a filename or a delimiter) 
static int	validate_redirect(t_token *list)
{
	t_token	*current;

	current = list;
	while (current)
	{
		if (current->type == IN || current->type == OUT
			|| current->type == APPEND || current->type == HEREDOC)
		{
			if (current->next == NULL || current->next->type != WORD)
			{
				ft_putstr_fd("Bashtard: syntax error around REDIRECTION "
					"sign\n", 2);
				return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}

// check for 3 edge cases only:
// 1. no pipe may be followed by another pipe
// 2. no pipe as the first node
// 3. no pipe as the last node.
static int	validate_pipes(t_token *list)
{
	t_token	*current;

	current = list;
	if (current && current->type == PIPE)
	{
		ft_putstr_fd("Bashtard: syntax error near "
			"unexpected token `|'\n", 2);
		return (-1);
	}
	while (current)
	{
		if (current->type == PIPE)
		{
			if (current->next == NULL || current->next->type == PIPE)
			{
				ft_putstr_fd("Bashtard: syntax error near "
					"unexpected token `|'\n", 2);
				return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}

int	input_validation(t_token *list)
{
	if (validate_pipes(list) == -1)
		return (-1);
	if (validate_redirect(list) == -1)
		return (-1);
	return (0);
}
