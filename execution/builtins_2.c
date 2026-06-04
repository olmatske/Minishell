/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:41:29 by olmatske          #+#    #+#             */
/*   Updated: 2026/06/04 21:30:18 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_exit(t_shell *shell, t_env **env, t_cmd_node *cmd)
{
	int	exit_status;

	if (!cmd->cmd->args[1])
		exit_status = shell->exit;
	else if (!isnumstr(cmd->cmd->args[1]))
	{
		fprintf(stderr, "exit\n"C_RED"%s exit: %s: %s\n"C_RESET,
			M, cmd->cmd->args[1], N);
		rl_clear_history();
		free_all(1, shell, env, cmd);
		exit (2);
	}
	else if (cmd->cmd->args[2])
	{
		exit_status = 1;
		fprintf(stderr, C_RED"%s %s\n"C_RESET, M, A);
		return (1);
	}
	else
		exit_status = ft_atoi(cmd->cmd->args[1]);
	rl_clear_history();
	free_all(1, shell, env, cmd);
	fprintf(stdout, "exit\n");
	exit(exit_status);
}

int	echo(char **str)
{
	int	i;
	int	n;

	i = 1;
	n = echo_n_check(str);
	if (n)
		i = 2;
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
	return (0);
}

static int	change_dir(t_shell *shell, char *target)
{
	char	old_path[PATHLEN];
	char	new_path[PATHLEN];

	if (!getcwd(old_path, sizeof(old_path)))
		return (perror("pre chdir: getcwd"), 1);
	if (chdir(target) == -1)
	{
		fprintf(stderr, C_RED"%s cd: %s: %s\n"C_RESET, M, target, FD);
		shell->exit = 1;
		return (1);
	}
	if (!getcwd(new_path, sizeof(new_path)))
		return (perror("post chdir: getcwd"), 1);
	update_pwd(shell->env, new_path, old_path);
	return (0);
}

int	cd(char **path, t_env *env, t_shell *shell)
{
	char	*target;
	char	*expansion;

	if (!path || !path[0])
		return (1);
	if (path[1] && path[2])
		return (fprintf(stderr, C_RED"%s cd: %s\n"C_RESET, M, A), 1);
	target = path[1];
	if (!target)
		expansion = expand_tilde("~", env);
	else
		expansion = expand_tilde(target, env);
	if (!expansion)
		return (fprintf(stderr, C_RED"%s HOME not set\n"C_RESET, M), 1);
	shell->exit = change_dir(shell, expansion);
	free(expansion);
	return (shell->exit);
}

int	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd");
		return (1);
	}
	if (path)
	{
		printf("%s\n", path);
		free(path);
	}
	return (0);
}
