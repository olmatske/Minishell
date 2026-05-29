/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_building.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:48:16 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/29 21:30:46 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

static void	distribute_redir(t_cmd_node *new_cmd, t_redir **tail, t_token *curr)
{
	t_redir	*node;

	node = create_new_redir_node(curr);
	add_node_to_redir_list(&new_cmd->cmd->redir, tail, node);
}

static void	distribute_word(t_cmd_node *new_cmd, t_token *current)
{
	int	i;

	i = 0;
	while (new_cmd->cmd->args[i] != NULL)
		i++;
	new_cmd->cmd->args[i] = ft_strdup(current->value);
	if (new_cmd->cmd->args[i] == NULL)
	{
		free_args(new_cmd->cmd->args);
		ft_error("Error: Memory allocation failed\n", 1);
	}
}

static t_token	*token_type_distributor(t_cmd_node *new_cmd, t_token *head)
{
	t_redir	*redir_tail;

	redir_tail = NULL;
	while (head != NULL && head->type != PIPE)
	{
		if (head->type == WORD)
			distribute_word(new_cmd, head);
		else if (head->type == IN || head->type == OUT
			|| head->type == APPEND || head->type == HEREDOC)
		{
			distribute_redir(new_cmd, &redir_tail, head);
			if (head->next != NULL)
				head = head->next;
		}
		head = head->next;
	}
	return (head);
}

t_cmd_node	*cmd_building(t_token *token_list)
{
	t_token		*current;
	t_cmd_node	*new_cmd;
	t_cmd_node	*head;
	t_cmd_node	*tail;

	current = token_list;
	head = NULL;
	tail = NULL;
	while (current)
	{
		new_cmd = create_empty_cmd_node();
		if (new_cmd == NULL)
			return (free_cmd_list(head), NULL);
		if (malloc_args_array(new_cmd, current) == -1)
			return (free_cmd_list(head), NULL);
		current = token_type_distributor(new_cmd, current);
		check_for_builtin(new_cmd);
		add_node_to_cmd_list(&head, &tail, new_cmd);
		if (current != NULL && current->type == PIPE)
			current = current->next;
	}
	return (head);
}
