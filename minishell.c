/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:33:42 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/10 13:48:20 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*shell_init(t_shell *shell, t_env **env)
{
	if (!shell)
	{
		shell = malloc(sizeof(t_shell));
		if (!shell)
			ft_error("shell malloc failure\n", 1);
	}
	shell->env = env;
	shell->gc = NULL;
	shell->exit = 0;
	return (shell);
}

static void	minishell_loop(t_env *copied_env)
{
	char		*line;
	t_cmd_node	*cmd_list;
	t_shell		*shell;

	shell = malloc(sizeof(t_shell)); // prev: shell = NULL;
	shell = shell_init(NULL, &copied_env); // prev after else statement in while loop
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
		if (cmd_list != NULL)
			shell_loop(shell, cmd_list);
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
	clear_history(); // changed from rl_clear_history to clear_history
	free_env_list(&copied_env);
	return (0);
}
