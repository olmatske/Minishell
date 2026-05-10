/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:52:51 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/10 17:38:12 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	wrapper_builtin(t_shell *shell, t_cmd_node *cmd_node, t_env **env)
{
	// printf("%s\n", *cmd->args);
	if (cmd_node->cmd->built_in_name == BUILTIN_NONE)
		return (1);
	else if (cmd_node->cmd->built_in_name == BUILTIN_ECHO)
		echo(cmd_node->cmd->args);                   // put away
	else if (cmd_node->cmd->built_in_name == BUILTIN_PWD)
		pwd();
	else if (cmd_node->cmd->built_in_name == BUILTIN_EXIT)
		ft_exit(shell, env, cmd_node);
	else if (cmd_node->cmd->built_in_name == BUILTIN_ENV)
		ft_env(*env);
	else if (cmd_node->cmd->built_in_name == BUILTIN_CD)
		cd(cmd_node->cmd->args[0]);
	else if (cmd_node->cmd->built_in_name == BUILTIN_EXPORT)
		export(shell, *env, ft_split(*cmd_node->cmd->args, '='));
	else if (cmd_node->cmd->built_in_name == BUILTIN_UNSET)
		unset(env, *cmd_node->cmd->args);
	return (0);
}

void	echo(char **str)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (!ft_strncmp(str[1], "-n ", 2))
	{
		n = 1;
		i = 2;
	}
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
	else
		return;
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
//probably will need args to free all of them etc
void	ft_exit(t_shell *shell, t_env **env, t_cmd_node *cmd)
{
	free_all(shell, env, cmd);
	exit(0);
}
void	ft_env(t_env *env)
{
	t_env *curr;

	curr = env;
	while (curr->next)
	{
		printf("%s%s\n", curr->name, curr->value);
		curr = curr->next;
	}
}

void	cd(char *path)
{
	if (chdir(path) == -1)
	{
		perror("Error");
		return;
	}
	// else
	// 	pwd();
}

// adds variable in shell: NAME=value
// updates variable's value if it already exists
// validate split
void	export(t_shell *shell, t_env *env, char **split)
{
	t_env	*curr;
	t_env	*new;

	curr = env;
	while (curr)
	{
		if (ft_strlen(curr->name) == ft_strlen(split[0])
			&& ft_strncmp(curr->name, split[0], ft_strlen(curr->name)) == 0)
			break;
		curr = curr->next;
	}
	if (curr)
		return (curr->value = split[1]);
	new = gc_malloc(shell, sizeof(t_env));
	new->name = ft_strdup(split[0]);
	new->value = split[1];
	new->next = NULL;
	if (split[1])
		new->value = ft_strdup(split[1]);
	while (env->next)
		env->next;
	env->next = new;
}

// removes variable in shell
void	unset(t_env **env, char *rm_var)
{
	t_env	*curr;
	t_env	*prev;
	t_env	*target;

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
	target = curr;
	if (!prev)
		*env = curr->next;
	else
		prev->next = curr->next;
	free(target);
}

