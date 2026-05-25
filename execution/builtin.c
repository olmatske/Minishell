/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:52:51 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/23 19:35:38 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	wrapper_builtin(t_shell *shell, t_cmd_node *cmd_node, t_env **env)
{
	char **split;

	split = NULL;
	if (cmd_node->cmd->built_in_name == BUILTIN_NONE)
		return (0);
	else if (cmd_node->cmd->built_in_name == BUILTIN_ECHO)
		echo(cmd_node->cmd->args);
	else if (cmd_node->cmd->built_in_name == BUILTIN_PWD)
		pwd();
	else if (cmd_node->cmd->built_in_name == BUILTIN_EXIT)
		ft_exit(shell, env, cmd_node);
	else if (cmd_node->cmd->built_in_name == BUILTIN_ENV)
		ft_env(env);
	else if (cmd_node->cmd->built_in_name == BUILTIN_CD)
		cd(cmd_node->cmd->args[1], *env, shell);
	else if (cmd_node->cmd->built_in_name == BUILTIN_EXPORT)
	{
		if (!cmd_node->cmd->args[1])
			return (print_export(env_array_for_execution(*env)), 0);
		split = ft_split(cmd_node->cmd->args[1], '=');
		if (split && split[0])
		{
			export(shell, env, cmd_node->cmd->args[1], split);
			free_split(split);
		}
		else
			return (fprintf(stderr, "%s ft_split failure", M), 1);
	}
	else if (cmd_node->cmd->built_in_name == BUILTIN_UNSET)
		unset(env, cmd_node->cmd->args[1]);
	return (0);
}

void	pwd(void)
{
	char *path = getcwd(NULL, 0);

	if (path)
	{
		printf("%s\n", path);
		free(path);
	}
	return;
}

void	ft_exit(t_shell *shell, t_env **env, t_cmd_node *cmd)
{
	int	exit_status;

	if (!cmd->cmd->args || !cmd->cmd->args[1])
		exit_status = shell->exit;
	else
		exit_status = ft_atoi(cmd->cmd->args[1]);
	rl_clear_history();
	free_all(shell, env, cmd);
	exit(exit_status);
}

void	ft_env(t_env **env)
{
	t_env *curr;

	curr = *env;
	while (curr)
	{
		if ((curr->name && ft_strncmp(curr->name, "?", 2) == 0) || curr->value == NULL)
		{
			if (curr->next == NULL)
				return ;
			curr = curr->next;
			continue;
		}
		printf("%s=%s\n", curr->name, curr->value);
		curr = curr->next;
	}
	printf("\n");
}

void	cd(char *path, t_env *env, t_shell *shell)
{
	t_env *curr;

	curr = env;
	if (!path || !ft_strcmp(path, "~"))
	{
		while (curr)
		{
			if (!ft_strcmp(curr->name, "HOME"))
			{
				path = curr->value;
				break;
			}
			curr = curr->next;
		}
		if (!path)
			printf("%s HOME not set\n", M);
	}
	if (chdir(path) == -1)
	{
		fprintf(stderr, "%s cd: no such file or directory: %s\n", M, path);
		shell->exit = 1;
		return ;
	}
}

void	export(t_shell *shell, t_env **env, char *arg, char **split)
{
	char	*equal;
	char	*name;
	char	*value;

	if (!arg)
		return ;
	equal = ft_strchr(arg, '=');
	if (equal == NULL)
	{
		if (!check_export(arg) || arg[0] == '=')
		{
			shell->exit = 1;
			fprintf(stderr, "%s '%s': not a valid identifier\n", M, arg);
			return ;
		}
		if (!check_var(*env, arg))
			append_variable(env, arg, NULL);
		return;
	}
	name = ft_substr(arg, 0, equal - arg);
	if (!name)
		return;
	if (!check_export(split[0]) || arg[0] == '=')
	{
		shell->exit = 1;
		fprintf(stderr, "%s '%s': not a valid identifier\n", M, arg);
		free(name);
		return ;
	}
	value = ft_strdup(equal + 1);
	if (!value)
		return (free(name));
	if (check_var(*env, name))
		update_variable(env, name, value);
	else
		append_variable(env, name, value);
	free(name);
	free(value);
}

// removes variable in shell
void	unset(t_env **env, char *rm_var)
{
	t_env	*curr;
	t_env	*prev;

	if (!env || !*env || !rm_var)
		return ;
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
		return ;
	if (!prev)
		*env = curr->next;
	else
		prev->next = curr->next;
	free(curr->name);
	free(curr->value);
	free(curr);
}

