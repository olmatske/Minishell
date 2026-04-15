#include "parsing.h"
#include "../minishell.h"

void	print_token_list_debug(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		printf("Token: %s\nType: %d\n", current->value, current->type);
		current = current->next;
	}
}

void	print_cmd_list_debug(t_cmd_node *head)
{
	t_cmd_node	*current;
	int			i;
	int			j;

	i = 0;
	current = head;
	while (current)
	{
		printf("Cmd node: %d\nBuiltin: %d\n", i, current->cmd->built_in_name);
		j = 0;
		printf("Cmd node args:\n");
		while (current->cmd->args[j])
		{
			printf("%s\n", current->cmd->args[j]);
			j++;
		}
		current = current->next;
		i++;
	}
}
