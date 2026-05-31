/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:46:55 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/31 14:01:40 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	process_heredocs(t_cmd_node *cmd_list, t_token *token_list,
		t_env *env)
{
	t_cmd_node	*current;
	t_redir		*curr_redir;
	int			counter;

	current = cmd_list;
	counter = 0;
	while (current)
	{
		curr_redir = current->cmd->redir;
		while (curr_redir)
		{
			if (curr_redir->heredoc_delimiter != NULL)
			{
				counter++;
				curr_redir->infile = heredoc(curr_redir->heredoc_delimiter,
						get_delimiter_quote_status(token_list,
							curr_redir->heredoc_delimiter), counter, env);
				if (curr_redir->infile == NULL)
					return (-1);
			}
			curr_redir = curr_redir->next;
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
		while (line[i] && ((line[i] >= '\t' && line[i] <= '\r')
				|| line[i] == ' '))
			i++;
		if (line[i] == '\0')
			break ;
		if (handle_type(&head, &tail, line, &i) == -1)
			return (free_list_token(&head), NULL);
	}
	return (head);
}

t_cmd_node	*main_parsing(char **line, t_env *copied_env)
{
	t_token		*token_list;
	t_cmd_node	*cmd_list;

	*line = check_quotes(*line);
	if (*line == NULL)
		return (NULL);
	token_list = create_tokens(*line);
	if (token_list == NULL)
		return (NULL);
	if (input_validation(token_list) == -1)
	{
		free_list_token(&token_list);
		return (NULL);
	}
	variable_substitution(&token_list, copied_env);
	cmd_list = cmd_building(token_list);
	if (cmd_list != NULL
		&& process_heredocs(cmd_list, token_list, copied_env) == -1)
	{
		free_list_token(&token_list);
		free_cmd_list(cmd_list);
		return (NULL);
	}
	free_list_token(&token_list);
	return (cmd_list);
}
