/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:46:55 by anshuval          #+#    #+#             */
/*   Updated: 2026/02/26 21:08:59 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

static void	free_list_token(t_token **head)
{
	t_token	*current;
	t_token	*next;

	if (head == NULL || (*head) == NULL)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->type);
		free(current->value);
		free(current);
		current = next;
	}
	*head = NULL;
}

static void	handle_words(char *line, int i)
{
	while (line[i])
	{
		
	}
}

static t_token	*create_node(t_token_type type, char *value)
{
	t_token	*new_node;

	new_node = malloc(sizeof (t_token));
	if (new_node == NULL)
		return (NULL);
	new_node->value = value;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

static void	add_to_token_linked_list(t_token_type type, t_token *node)
{
	
}

void	main_parsing(char *line)
{
	int		i;
	t_token	*new_node;

	i = 0;
	while (line[i])
	{
		while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
			i++;
		if (line[i] == '|')
		{
			new_node = create_node(PIPE, "|");
			if (new_node == NULL)
			{
				free_list_token(new_node);
				return (NULL);
			}
			add_to_token_linked_list(PIPE, new_node);
		}
		else if (line[i] == '>')
		{
			new_node = create_node(IN, ">");
			{
				free_list_token(new_node);
				return (NULL);
			}
			add_to_token_linked_list(IN, new_node);
		}
		else if (line[i] == '<')
		{
			new_node = create_node(OUT, "<");
			{
				free_list_token(new_node);
				return (NULL);
			}
			add_to_token_linked_list(OUT, new_node);
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			new_node = create_node(HEREDOC, ">>");
			{
				free_list_token(new_node);
				return (NULL);
			}
			add_to_token_linked_list(HEREDOC, new_node);
			i++;
		}
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			new_node = create_node(APPEND, "<<");
			{
				free_list_token(new_node);
				return (NULL);
			}
			add_to_token_linked_list(APPEND, new_node);
			i++;
		}
		else
			handle_words(line, i);
		i++;
	}
}

// check there is exactly one argument when initially running the program - the ./minishell 123 should not work
// save the envp into linked list in the shell_env
// increment the shllvl  for the new envp (and each time the minishell is opened inside minishell)
// validate the input inside the minishell- in validation
// by using the delimiter of space or space-like characters (split??)
// parse input line and search for 5 symbols: | < > << >>, and for words. 
// save each of the found symbols / words in a separate node
// create a linked list
// validate the input - the pipe can only be between two commands (with arguments), and only one pipe,
// redirections should have either a filename or a word(that will be turned sowieso into a file name)
// group tokens into commands in the struct s_cmd
