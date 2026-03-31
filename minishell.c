/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:33:42 by anshuval          #+#    #+#             */
/*   Updated: 2026/03/31 16:58:49 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_loop(t_env *copied_env)
{
	char		*line;
	t_cmd_node	*cmd_list;

	replace_signals();
	while (1)
	{
		line = readline("Minishell$");
		if (line == NULL)
			break;
		else if (line[0] == '\0' || is_it_space_only(line) == 1)
		{
			free(line);
			continue;
		}
		else
			add_history(line);
		cmd_list = main_parsing(line);
		if (cmd_list != NULL)
			shell_loop(copied_env, cmd_list);
		free(line);
		free_cmd_list(cmd_list);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*copied_env;

	(void)argv;
	copied_env = NULL;
	if (argc != 1)
	{
		printf("Minishell does not accept arguments. "
			"Type in only ./Minishell to enter Minishell\n");
		return (1);
	}
	copied_env = shell_env(envp);
	if (copied_env == NULL)
		ft_error("Failed to copy environment.\n", 1);
	minishell_loop(copied_env);
	rl_clear_history();
	free_env_list(&copied_env);
	return (0);
}

// add the call for main  parsing - change the return values - to t_cmd_node??
// rename the shell loop into execution for readability and pass there also the commands, not only the environment(to be talked over witrh Olya)
// check that the cmd_list was successfull. if yes, then call the executiobn else free the list
// add the free commaand list function
// free the line directly
// what should be done if line == null
// 		if line == NULL - means the user has passed the ctrl D to exit. break out of it
// what should be done if the data of the printed in is empty
// 		add the check for the enter - that is the empty line. should not be added to the history
// only add to history if smth was actually printed. but the cmd list should still be called to return a null and break ouut of the function
// free the copied env at t the very end!
// add the allowed built in function rl_clearhistory. 