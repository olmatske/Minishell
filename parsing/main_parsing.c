/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:46:55 by anshuval          #+#    #+#             */
/*   Updated: 2026/04/06 18:47:02 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

static t_token	*create_tokens(char *line)
{
	int		i;
	t_token	*head;
	t_token	*tail;

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
			return (NULL);
	}
	return (head);
}

t_cmd_node	*main_parsing(char *line, t_env *copied_env)
{
	t_token		*token_list;
	t_cmd_node	*cmd_list;

	if (check_quotes(line) == NO)
		return (NULL);
	token_list = create_tokens(line);
	if (token_list == NULL)
		return (NULL);
	if (input_validation(token_list) == -1)
	{
		free_list_token(&token_list);
		return (NULL);
	}
	variable_substitution(&token_list, copied_env);
	cmd_list = cmd_building(token_list);
	free_list_token(&token_list);
	return (cmd_list);
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
//  validate the input inside the minishell- in validation by nodes
//  validate the input - the pipe can only be between two commands (with arguments), and only one pipe,
//  redirections should have either a filename or a word(that will be turned sowieso into a file name)
// group tokens into commands in the struct s_cmd
