/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:46:55 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/29 18:17:47 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

static int	process_heredocs(t_cmd_node *cmd_list, t_env *env)
{
	t_cmd_node	*current;
	t_redir		*current_redir;
	int			counter;

	current = cmd_list;
	counter = 0;
	while(current)
	{
		current_redir = current->cmd->redir;
		while (current)
		{
			if (current_redir->heredoc_delimiter != NULL)
			{
				counter++;
				current_redir->infile = heredoc(current_redir->heredoc_delimiter, counter, env);
				if (current_redir->infile == -1)
					return (-1);
			}
			current_redir = current_redir->next;
		}
		current = current->next;
	}
	return (0);
}

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
			return (free_list_token(&head), NULL);
	}
	return (head);
}

t_cmd_node	*main_parsing(char *line, t_env *copied_env)
{
	t_token		*token_list;
	t_cmd_node	*cmd_list;

	check_quotes(line);
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
	if (cmd_list != NULL)
	{
		if (process_heredocs(cmd_list, copied_env) == -1)
		{
			free_cmd_list(cmd_list);
			return (NULL);
		}
	}
	return (cmd_list);
}
