/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:24:25 by anshuval          #+#    #+#             */
/*   Updated: 2026/04/14 13:45:32 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

static void	just_copy(char *old_w, int *i, char **new_w)
{
	*new_w = append_char(*new_w, old_w[*i]);
	(*i)++;
}

static void	expand_env(char *old_w, int *i, char **new_w, t_env *env)
{
	int		start;
	char	*name;
	char	*value;

	(*i)++;
	if (old_w[*i] == '\0' || old_w[*i] == ' ' || old_w[*i] == '\''
		|| old_w[*i] == '\"')
	{
		*new_w = append_char(*new_w, '$');
		return ;
	}
	start = *i;
	if (old_w[*i] == '?')
		(*i)++;
	else
	{
		while (old_w[*i] && (ft_isalnum(old_w[*i]) || old_w[*i] == '_'))
			(*i)++;
	}
	name = ft_substr(old_w, start, *i - start);
	value = search_env(env, name);
	free(name);
	*new_w = append_str(*new_w, value);
}

static void	search_for_dollar(char *old_w, int *i, char **new_w, t_env *env)
{
	if (old_w[*i] == '$')
		expand_env(old_w, i, new_w, env);
	else
		just_copy(old_w, i, new_w);
}

static void	substitute_word(t_token **list, t_token *word, t_env *copied_env)
{
	int		in_single;
	int		in_double;
	int		i;
	char	*new_line;

	in_single = NO;
	in_double = NO;
	i = 0;
	new_line = NULL;
	while (word->value[i])
	{
		if (quote_status(word->value[i], &in_double, &in_single) == YES)
			i++;
		else if (in_single == YES)
			just_copy(word->value, &i, &new_line);
		else
			search_for_dollar(word->value, &i, &new_line, copied_env);
	}
	free(word->value);
	word->value = new_line;
	if (word->value == NULL || (word->value[0] == '\0'
			&& in_single != YES && in_double != YES))
		delete_empty_node(list, word);
}

void	variable_substitution(t_token **token_list, t_env *copied_env)
{
	t_token	*current;
	t_token	*next;

	current = *token_list;
	while (current)
	{
		next = current->next;
		if (current->type == WORD)
			substitute_word(token_list, current, copied_env);
		current = next;
	}
}
