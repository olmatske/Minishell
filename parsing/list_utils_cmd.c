/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:33:49 by anshuval          #+#    #+#             */
/*   Updated: 2026/03/31 17:58:44 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

static void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free (args[i]);
		i++;
	}
	free(args);
}

void	free_cmd_list(t_cmd_node *head)
{
	t_cmd_node	*current;
	t_cmd_node	*next;

	if (head == NULL)
		return ;
	current = head;
	while (current)
	{
		next = current->next;
		if (current->cmd)
		{
			if (current->cmd->args)
				free_args(current->cmd->args);
			free(current->cmd->redir);
			free(current->cmd);
		}
		free(current);
		current = next;
	}
}
