/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:24:25 by anshuval          #+#    #+#             */
/*   Updated: 2026/06/03 22:06:02 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	delete_empty_node(t_token **head, t_token *to_delete)
{
	t_token	*current;
	t_token	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (current == to_delete)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static char	*dollars_and_quotes(char *value, t_env *env, int *had_quotes,
		int is_delimiter)
{
	int		in_single;
	int		in_double;
	int		i;
	char	*new_line;

	in_single = NO;
	in_double = NO;
	i = 0;
	new_line = NULL;
	while (value[i])
	{
		if (i == 0 && value[i] == '~' && (value[i + 1] == '\0'
				|| value[i + 1] == '/'))
			new_line = tilde(env, &i, new_line);
		else if (quote_status(value[i], &in_double, &in_single) == YES)
		{
			*had_quotes = YES;
			i++;
		}
		else if (in_single == YES || is_delimiter == YES)
			just_copy(value, &i, &new_line);
		else
			search_dollar_or_copy(value, &i, &new_line, env);
	}
	return (new_line);
}

static int	check_ambiguous_redirect(char *new, char *old, t_token *prev,
		t_env *env)
{
	if (new == NULL || new[0] == '\0')
	{
		if (prev != NULL && (prev->type == IN || prev->type == OUT
				|| prev->type == APPEND || prev->type == HEREDOC))
		{
			ft_putstr_fd("Minishell: ", STDERR_FILENO);
			ft_putstr_fd(old, STDERR_FILENO);
			ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
			free(new);
			exit_status(env, 1);
			return (-1);
		}
	}
	return (0);
}

static int	substitute_word(t_token **list, t_token *word, t_token *prev,
		t_env *env)
{
	int		had_quotes;
	int		is_delimiter;
	char	*new_line;

	had_quotes = NO;
	is_delimiter = NO;
	if (prev != NULL && prev->type == HEREDOC)
		is_delimiter = YES;
	new_line = dollars_and_quotes(word->value, env,
			&had_quotes, is_delimiter);
	if (had_quotes == NO && check_ambiguous_redirect(new_line, word->value,
			prev, env) == -1)
		return (-1);
	word->was_quoted = had_quotes;
	free(word->value);
	word->value = new_line;
	if (word->value == NULL && had_quotes == YES)
	{
		word->value = ft_strdup("");
		if (word->value == NULL)
			return (-1);
	}
	if (word->value == NULL || (word->value[0] == '\0' && had_quotes != YES))
		delete_empty_node(list, word);
	return (0);
}

int	variable_substitution(t_token **token_list, t_env *copied_env)
{
	t_token	*current;
	t_token	*prev;
	t_token	*next;

	current = *token_list;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (current->type == WORD)
		{
			if (substitute_word(token_list, current, prev, copied_env) == -1)
				return (-1);
		}
		prev = current;
		current = next;
	}
	return (0);
}
