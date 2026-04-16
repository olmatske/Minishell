/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:46:55 by anshuval          #+#    #+#             */
/*   Updated: 2026/04/16 15:14:59 by anshuval         ###   ########.fr       */
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
			return (free_list_token(&head), NULL);
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
	printf("before substitution\n");
	print_token_list_debug(token_list);
	variable_substitution(&token_list, copied_env);
	printf("after substitution\n");
	print_token_list_debug(token_list);
	cmd_list = cmd_building(token_list);
	printf("cmd_list created:\n");
	print_token_list_debug(token_list);
	free_list_token(&token_list);
	printf("CMD LIST CREATED:\n");
	print_cmd_list_debug(cmd_list);
	return (cmd_list);
}
