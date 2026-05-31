/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:33:42 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/31 15:46:22 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static t_shell	*shell_init(t_shell *shell, t_env **env)
{
	if (!shell) // added
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

static void	execute(char **line, t_env *copied_env, t_shell *shell)
{
	t_cmd_node	*cmd_list;

	add_history(*line);
	cmd_list = main_parsing(line, copied_env);
	if (cmd_list != NULL)
		shell_loop(shell, cmd_list);
	free_cmd_list(cmd_list);
}

static void	minishell_loop(t_env *copied_env, t_shell *shell)
{
	char		*line;

	replace_signals();
	while (1)
	{
		g_signal = 0;
		line = readline("Minishell$ ");
		if (g_signal == 130)
		{
			shell->exit = 130;
			update_shell_status(&copied_env, shell);
		}
		if (line == NULL)
			break ;
		if (line[0] != '\0' && is_it_space_only(line) != 1)
			execute(&line, copied_env, shell);
		free(line);
	}
	free_all(shell, NULL, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*copied_env;
	t_shell		*shell;

	(void)argv;
	copied_env = NULL;
	shell = shell_init(NULL, &copied_env); // prev after else statement in while loop
	if (argc != 1)
	{
		printf("Minishell does not accept arguments. "
			"Type in only ./Minishell to enter Minishell\n");
		free(shell);
		return (1);
	}
	copied_env = shell_env(envp);
	if (copied_env == NULL)
		ft_error("Failed to copy environment.\n", 1);
	minishell_loop(copied_env, shell);
	rl_clear_history(); // changed from rl_clear_history to clear_history
	free_env_list(&copied_env);
	return (0);
}
