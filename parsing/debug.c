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
