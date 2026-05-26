/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:52:51 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/26 10:14:50 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	wrapper_builtin(t_shell *shell, t_cmd_node *cmd_node, t_env **env)
{
	char	**split;
	int		exit;

	split = NULL;
	exit = 0;

	if (cmd_node->cmd->built_in_name == BUILTIN_NONE)
		return (0);
	else if (cmd_node->cmd->built_in_name == BUILTIN_ECHO)
		exit = echo(cmd_node->cmd->args);
	else if (cmd_node->cmd->built_in_name == BUILTIN_PWD)
		exit = pwd();
	else if (cmd_node->cmd->built_in_name == BUILTIN_EXIT)
		exit = ft_exit(shell, env, cmd_node);
	else if (cmd_node->cmd->built_in_name == BUILTIN_ENV)
		exit = ft_env(env);
	else if (cmd_node->cmd->built_in_name == BUILTIN_CD)
		exit = cd(cmd_node->cmd->args, *env, shell);
	else if (cmd_node->cmd->built_in_name == BUILTIN_EXPORT)
	{
		if (!cmd_node->cmd->args[1])
			return (print_export(env_array_for_execution(*env)), 0);
		split = ft_split(cmd_node->cmd->args[1], '=');
		if (split && split[0])
		{
			exit = export(shell, env, cmd_node->cmd->args[1], split);
			free_split(split);
		}
		else
		{
			return (fprintf(stderr, "%s %s", M, I), 1);
		}
	}
	else if (cmd_node->cmd->built_in_name == BUILTIN_UNSET)
		exit = unset(env, cmd_node->cmd->args[1]);
	// printf("DEBUG WRAPPER: exit: %d\n", exit);
	return (exit);
}

int	pwd(void)
{
	char *path = getcwd(NULL, 0);

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

int	ft_exit(t_shell *shell, t_env **env, t_cmd_node *cmd)
{
	int	exit_status;

	printf("exit\n");
	if (!cmd->cmd->args[1])
		exit_status = shell->exit;
	else if (!isnumstr(cmd->cmd->args[1]))
	{
		fprintf(stderr, "%s %s: %s\n", M, cmd->cmd->args[1], N);
		rl_clear_history();
		free_all(shell, env, cmd);
		exit (2);
	}
	else if (cmd->cmd->args[2])
	{
		exit_status = 1;
		fprintf(stderr, "%s %s\n", M, A);
		return (1);
	}
	else
		exit_status = ft_atoi(cmd->cmd->args[1]);
	rl_clear_history();
	free_all(shell, env, cmd);
	exit(exit_status);
}

int	ft_env(t_env **env)
{
	t_env *curr;

	curr = *env;
	while (curr)
	{
		if ((curr->name && ft_strncmp(curr->name, "?", 2) == 0) || curr->value == NULL)
		{
			if (curr->next == NULL)
				return (1);
			curr = curr->next;
			continue;
		}
		printf("%s=%s\n", curr->name, curr->value);
		curr = curr->next;
	}
	printf("\n");
	return (0);
}

int	cd(char **path, t_env *env, t_shell *shell)
{
	t_env *curr;

	curr = env;
	if (path[2])
		return (fprintf(stderr, "%s cd: %s\n", M, A), 1);
	if (!path || !ft_strcmp(path[1], "~"))
	{
		while (curr)
		{
			if (!ft_strcmp(curr->name, "HOME"))
			{
				path = &curr->value;
				break;
			}
			curr = curr->next;
		}
		if (!path[1])
			fprintf(stderr, "%s HOME not set\n", M);
	}
	if (chdir(path[1]) == -1)
	{
		fprintf(stderr, "%s %s: cd: %s\n", M, path[1], FD);
		shell->exit = 1;
		return (1);
	}
	return (0);
}

int	export(t_shell *shell, t_env **env, char *arg, char **split)
{
	char	*equal;
	char	*name;
	char	*value;

	if (!arg)
		return (1);
	equal = ft_strchr(arg, '=');
	if (equal == NULL)
	{
		if (!check_export(arg) || arg[0] == '=')
		{
			shell->exit = 1;
			fprintf(stderr, "%s '%s': %s\n", M, arg, I);
			return (1);
		}
		if (!check_var(*env, arg))
			append_variable(env, arg, NULL);
		return (0);
	}
	name = ft_substr(arg, 0, equal - arg);
	if (!name)
		return (1);
	if (!check_export(split[0]) || arg[0] == '=')
	{
		shell->exit = 1;
		fprintf(stderr, "%s '%s': %s\n", M, arg, I);
		free(name);
		return (1);
	}
	value = ft_strdup(equal + 1);
	if (!value)
		return (free(name), 1);
	if (check_var(*env, name))
		update_variable(env, name, value);
	else
		append_variable(env, name, value);
	free(name);
	free(value);
	return (0);
}

// removes variable in shell
int	unset(t_env **env, char *rm_var)
{
	t_env	*curr;
	t_env	*prev;

	if (!env || !*env || !rm_var)
		return (0);
	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strlen(curr->name) == ft_strlen(rm_var)
			&& ft_strncmp(curr->name, rm_var, ft_strlen(curr->name)) == 0)
			break;
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return (0);
	if (!prev)
		*env = curr->next;
	else
		prev->next = curr->next;
	free(curr->name);
	free(curr->value);
	free(curr);
	return (0);
}

