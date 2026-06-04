/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:33:42 by anshuval          #+#    #+#             */
/*   Updated: 2026/06/04 19:57:32 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static t_shell	*shell_init(t_shell *shell, t_env **env)
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

char	*get_input_line(const char *prompt)
{
	char	*line;
	char	*trimmed;

	if (isatty(STDIN_FILENO))
		line = readline(prompt);
	else
	{
		line = get_next_line(STDIN_FILENO);
		if (line != NULL)
		{
			trimmed = ft_strtrim(line, "\n");
			free(line);
			line = trimmed;
		}
	}
	return (line);
}

static void	execute(char **line, t_env *copied_env, t_shell *shell)
{
	t_cmd_node	*cmd_list;
	char		*status;

	if (isatty(STDIN_FILENO))
		add_history(*line);
	status = NULL;
	cmd_list = main_parsing(line, copied_env);
	if (cmd_list != NULL)
		shell_loop(shell, cmd_list);
	else
	{
		if (g_signal == 130)
		{
			shell->exit = 130;
			exit_status(copied_env, 130);
		}
		else
		{
			status = search_env(copied_env, "?");
			if (status)
				shell->exit = ft_atoi(status);
		}
	}
	free_cmd_list(cmd_list);
}

static void	minishell_loop(t_env *copied_env, t_shell *shell)
{
	char		*line;

	replace_signals();
	while (1)
	{
		g_signal = 0;
		line = get_input_line(C_CYAN"Bashtard$ " C_RESET);
		if (g_signal == 130)
		{
			shell->exit = 130;
			update_shell_status(&copied_env, shell);
		}
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (line[0] != '\0' && is_it_space_only(line) != 1)
			execute(&line, copied_env, shell);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*copied_env;
	t_shell		*shell;
	int			exit_code;

	(void)argv;
	copied_env = NULL;
	shell = shell_init(NULL, &copied_env);
	if (argc != 1)
	{
		printf("This Bashtard does not start unless you type in only "
			"./bashtard.\n");
		free(shell);
		return (1);
	}
	copied_env = shell_env(envp);
	if (copied_env == NULL)
		ft_error("Failed to copy environment.\n", 1);
	minishell_loop(copied_env, shell);
	exit_code = shell->exit;
	free_all(0, shell, NULL, NULL);
	rl_clear_history();
	free_env_list(&copied_env);
	return (exit_code);
}
