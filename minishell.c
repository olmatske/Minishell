/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:33:42 by anshuval          #+#    #+#             */
/*   Updated: 2026/03/22 20:09:48 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*copied_env;
	t_cmd_node	*cmd_list;

	(void)argv;
	copied_env = NULL;
	if (argc != 1)
	{
		printf("Minishell does not accept arguments. "
			"Type in only ./Minishell to enter Minishell\n");
		return (1);
	}
	copied_env = shell_env(envp);
	while (1)
	{
		line = readline("Minishell$");
		if (line != NULL)
			add_history(line);
		cmd_list = main_parsing(line);
		shell_loop(copied_env, cmd_list);
	}
	return (0);
}

// add the call for main  parsing - change the return values - to t_cmd_node??
// rename the shell loop into execution fi=or readability and pass there also the commands, not only the environment(to be talked over witrh Olya)
// check that the cmd_list was successfull. if yes, then call the executiobn else free the list
// add the free commaand list function
// add the free line function? is it malloced?
// move everythhing inside the if line != null part?
// what should be done if line == null
// what should be done if the data of the printed in is empty
// only add to history if smth was actually printed. but the cmd list should still be called to return a null and break ouut of the function
// free the copied env at t the very end!