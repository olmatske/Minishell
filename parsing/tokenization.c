/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:24:18 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/26 13:23:16 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

static int	get_word_length(char *line, int i)
{
	int	inside_single_quotes;
	int	inside_double_quotes;
	int	len;

	inside_single_quotes = NO;
	inside_double_quotes = NO;
	len = 0;
	while (line[i + len])
	{
		if (line[i + len] == '\"' && inside_single_quotes == NO)
			inside_double_quotes = !inside_double_quotes;
		else if (line[i + len] == '\'' && inside_double_quotes == NO)
			inside_single_quotes = !inside_single_quotes;
		if (inside_single_quotes == NO && inside_double_quotes == NO)
		{
			if ((line[i + len] >= 9 && line[i + len] <= 13)
				|| line[i + len] == 32
				|| line[i + len] == '|'
				|| line[i + len] == '>'
				|| line[i + len] == '<')
				break ;
		}
		len++;
	}
	return (len);
}

static void	handle_words(t_token **head, t_token **tail, char *line, int *i)
{
	int			len;
	char		*value;

	len = get_word_length(line, *i);
	if (len < 1)
		return ;
	value = ft_substr(line, *i, len);
	if (value == NULL)
		return ;
	if (linked_list_for_token(head, tail, WORD, value) == -1)
	{
		free(value);
		return ;
	}
	*i = *i + len;
	free(value);
}

// changed the flags of APPEND, HEREDOC etc, they were mixed up
static int	handle_redir(t_token **head, t_token **tail, char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		(*i) += 2;
		return (linked_list_for_token(head, tail, APPEND, ">>"));
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		(*i) += 2;
		return (linked_list_for_token(head, tail, HEREDOC, "<<"));
	}
	else if (line[*i] == '>')
	{
		(*i)++;
		return (linked_list_for_token(head, tail, OUT, ">"));
	}
	else if (line[*i] == '<')
	{
		(*i)++;
		return (linked_list_for_token(head, tail, IN, "<"));
	}
	return (1);
}

int	handle_type(t_token **head, t_token **tail, char *line, int *i)
{
	int	redir_status;

	if (line[*i] == '|')
	{
		(*i)++;
		return (linked_list_for_token(head, tail, PIPE, "|"));
	}
	redir_status = handle_redir(head, tail, line, i);
	if (redir_status != 1)
		return (redir_status);
	handle_words(head, tail, line, i);
	return (0);
}
