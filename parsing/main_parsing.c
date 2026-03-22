/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:46:55 by anshuval          #+#    #+#             */
/*   Updated: 2026/03/22 20:29:16 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

static t_token	*create_new_token_node(t_token_type type, char *value)
{
	t_token	*new_node;

	new_node = malloc(sizeof (t_token));
	if (new_node == NULL)
		return (NULL);
	new_node->value = ft_strdup(value);
	if (new_node->value == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

static int	linked_list_for_token(t_token **head, t_token **tail,
	t_token_type type, char *str)
{
	t_token	*new_node;

	new_node = create_new_token_node(type, str);
	if (new_node == NULL)
	{
		free_list_token(&head);
		return (-1);
	}
	add_node_to_token_list(&head, &tail, new_node);
	return (0);
}

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
			if ((line[i + len] >= 9 && line[i + len] <= 13) || line[i + len] == 32
				|| line[i + len] == '|' || line[i + len] == '>'
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
		return ;
	*i = *i + len;
}

static int	handle_type(t_token **head, t_token **tail, char *line, int *i)
{
	if (line[*i] == '|')
		return (linked_list_for_token(head, tail, PIPE, "|"));
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		i++;
		return (linked_list_for_token(head, tail, HEREDOC, ">>"));
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		i++;
		return (linked_list_for_token(head, tail, APPEND, "<<"));
	}
	else if (line[*i] == '>')
		return (linked_list_for_token(head, tail, IN, ">"));
	else if (line[*i] == '<')
		return (linked_list_for_token(head, tail, OUT, "<"));
	else
		handle_words(head, tail, line, i);
	i++;
}

t_cmd_node	*main_parsing(char *line)
{
	int		i;
	t_token	*head;
	t_token	*tail;

	if (check_quotes(line) == NO)
		return ;
	i = 0;
	head = NULL;
	tail = NULL;
	while (line[i])
	{
		while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
			i++;
		if (line[i] == '\0')
			break ;
		if (handle_type(&head, &tail, line, &i) == -1)
			return ;
		i++;
	}
	print_token_list_debug(head);
	return (head);
}

// 	search for the equal sign in eac separate envp
// 	left to the equal sign is the name
// 	right to the equal sign is the value
// 	pass both to the new node
// 	append the nodes

// 	check there is exactly one argument when initially running the program - the ./minishell 123 should not work
// 	save the envp into linked list in the shell_env
// 	by using the delimiter of space or space-like characters (split??)
// 	parse input line and search for 5 symbols: | < > << >>, and for words. 
// 	save each of the found symbols / words in a separate node
// 	create a linked list
// 	increment the shllvl  for the new envp (and each time the minishell is opened inside minishell)
// validate the input inside the minishell- in validation by nodes
// validate the input - the pipe can only be between two commands (with arguments), and only one pipe,
// redirections should have either a filename or a word(that will be turned sowieso into a file name)
// group tokens into commands in the struct s_cmd
