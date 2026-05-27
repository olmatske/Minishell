/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_building.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:48:16 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/27 14:32:54 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../execution/execution.h"
#include "../minishell.h"

static void	redir_builder(char **file_type, t_token *current)
{
	char	*filename;

	if (*file_type != NULL)
		free(*file_type);
	if (current->next == NULL || current->next->type == IN 
		|| current->next->type == OUT || current->next->type == APPEND 
		|| current->next->type == HEREDOC)
		ft_error("Syntax error near unsexpected token 'newline'\n", 2);
	filename = current->next->value;
	if (current->type == IN && access(filename, R_OK) == -1)
	{
		fprintf(stderr, "%s %s: %s\n", M, filename, strerror(errno));
		// exit(1);
	}
	if ((current->type == OUT || current->type == APPEND) 
		&& access(filename, W_OK) == -1 && errno != ENOENT)
	{
		fprintf(stderr, "%s %s: %s\n", M, filename, strerror(errno));
		// exit(1);
	}
	*file_type = ft_strdup(current->next->value);
	if (*file_type == NULL)
		ft_error("Error: Memory allocation failed\n", 1);
}
// static void	redir_builder(char **file_type, t_token *current)
// {
// 	if (*file_type != NULL)
// 		free(*file_type);
// 	if (current->next == NULL || current->next->type == IN 
// 		|| current->next->type == OUT || current->next->type == APPEND 
// 		|| current->next->type == HEREDOC)
// 		ft_error("Syntax error near unsexpected token 'newline'\n", 2);
// 	*file_type = ft_strdup(current->next->value);
// 	if (*file_type == NULL)
// 		ft_error("Error: Memory allocation failed\n", 1);
// }


// static void	distribute_redir(t_cmd_node *cmd, t_token *current)
// {
// 	t_redir	*new;

// 	if (!cmd->cmd->redir_list)
// 		cmd
// }

// deleted: new_cmd->cmd->redir->out_type = IN_FILE; line 32 - 33
static void	distribute_redir(t_cmd_node *new_cmd, t_token *current)
{
	if (new_cmd->cmd->redir == NULL)
	{
		new_cmd->cmd->redir = ft_calloc(1, sizeof (t_redir));
		if (new_cmd->cmd->redir == NULL)
			ft_error("Error: Memory allocation failed\n", 1);
	}
	if (current->type == IN)
		redir_builder(&new_cmd->cmd->redir->infile, current);
	else if (current->type == OUT || current->type == APPEND)
	{
		if (current->type == OUT)
			new_cmd->cmd->redir->out_type = OUT_OVERWRITE;
		else if (current->type == APPEND)
			new_cmd->cmd->redir->out_type = OUT_APPEND;
		redir_builder(&new_cmd->cmd->redir->outfile, current);
	}
	else if (current->type == HEREDOC)
		redir_builder(&new_cmd->cmd->redir->heredoc_delimiter, current);
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
	while (head != NULL && head->type != PIPE)
	{
		if (head->type == WORD)
			distribute_word(new_cmd, head);
		else if (head->type == IN || head->type == OUT
			|| head->type == APPEND || head->type == HEREDOC)
		{
			distribute_redir(new_cmd, head);
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


// static void	distribute_redir(t_cmd_node *new_cmd, t_token *current)
// {
// 	if (new_cmd->cmd->redir == NULL)
// 	{
// 		new_cmd->cmd->redir = ft_calloc(1, sizeof (t_redir));
// 		if (new_cmd->cmd->redir == NULL)
// 			ft_error("Error: Memory allocation failed\n", 1);
// 		new_cmd->cmd->redir->out_type = IN_FILE;
// 	}
// 	if (current->type == IN)
// 		redir_builder(&new_cmd->cmd->redir->infile, current);
// 	else if (current->type == OUT || current->type == APPEND)
// 	{
// 		if (current->type == OUT)
// 			new_cmd->cmd->redir->out_type = OUT_OVERWRITE;
// 		else if (current->type == APPEND)
// 			new_cmd->cmd->redir->out_type = OUT_APPEND;
// 		redir_builder(&new_cmd->cmd->redir->outfile, current);
// 	}
// 	else if (current->type == HEREDOC)
// 		redir_builder(&new_cmd->cmd->redir->heredoc_delimiter, current);
// }