/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:41:29 by olmatske          #+#    #+#             */
/*   Updated: 2026/06/05 14:36:26 by olmatske         ###   ########.fr       */
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
		printf("exit\n");
		ft_puterr("exit", cmd->cmd->args[1], N, 1);
		rl_clear_history();
		free_all(1, shell, env, cmd);
		exit (2);
	}
	else if (cmd->cmd->args[2])
	{
		exit_status = 1;
		ft_puterr(A, NULL, NULL, 1);
		return (1);
	}
	else
		exit_status = ft_atoi(cmd->cmd->args[1]);
	rl_clear_history();
	free_all(1, shell, env, cmd);
	printf("exit\n");
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
		ft_puterr("cd", target, FD, 1);
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
		return (ft_puterr("cd", A, NULL, 1), 1);
	target = path[1];
	if (!target)
		expansion = expand_tilde("~", env);
	else
		expansion = expand_tilde(target, env);
	if (!expansion)
		return (ft_puterr("HOME not set", NULL, NULL, 1), 1);
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
