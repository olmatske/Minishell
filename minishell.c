/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:33:42 by anshuval          #+#    #+#             */
/*   Updated: 2026/04/15 18:10:27 by anshuval         ###   ########.fr       */
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
		line = readline("Minishell$ ");
		if (line == NULL)
			break ;
		else if (line[0] == '\0' || is_it_space_only(line) == 1)
		{
			free(line);
			continue ;
		}
		else
			add_history(line);
		cmd_list = main_parsing(line, copied_env);
		// if (cmd_list != NULL)
		// 	shell_loop(copied_env, cmd_list);
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
