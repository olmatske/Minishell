/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:52:51 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/11 16:32:15 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	wrapper_builtin(t_shell *shell, t_cmd_node *cmd_node, t_env **env)
{
	char **split;

	split = NULL;
	if (cmd_node->cmd->built_in_name == BUILTIN_NONE)
		return (1);
	else if (cmd_node->cmd->built_in_name == BUILTIN_ECHO)
		echo(cmd_node->cmd->args);
	else if (cmd_node->cmd->built_in_name == BUILTIN_PWD)
		pwd();
	else if (cmd_node->cmd->built_in_name == BUILTIN_EXIT)
		ft_exit(shell, env, cmd_node);
	else if (cmd_node->cmd->built_in_name == BUILTIN_ENV)
		ft_env(env);
	else if (cmd_node->cmd->built_in_name == BUILTIN_CD)
		cd(cmd_node->cmd->args[1]);
	else if (cmd_node->cmd->built_in_name == BUILTIN_EXPORT)
	{
		split = ft_split(cmd_node->cmd->args[1], '=');
		if (split)
		{
			export(shell, env, split);
			free_split(split);
		}
	}
	else if (cmd_node->cmd->built_in_name == BUILTIN_UNSET)
		unset(env, cmd_node->cmd->args[1]);
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

void	ft_exit(t_shell *shell, t_env **env, t_cmd_node *cmd)
{
	free_all(shell, env, cmd);
	exit(shell->exit);
}
void	ft_env(t_env **env)
{
	t_env *curr;

	curr = *env;
	while (curr)
	{
		if (curr->name && ft_strncmp(curr->name, "?", 2) == 0)
		{
			curr = curr->next;
			continue;
		}
		printf("%s=%s\n", curr->name, curr->value);
		curr = curr->next;
	}
	printf("\n");
}

void	cd(char *path)
{
	if (chdir(path) == -1)
	{
		perror("Error");
		return;
	}
}

// adds variable in shell: NAME=value
// updates variable's value if it already exists
// validate split
void	export(t_shell *shell, t_env **env, char **split)
{
	t_env	*curr;
	t_env	*new;

	curr = *env;
	if (!split)
	while (curr)
	{
		if (ft_strlen(curr->name) == ft_strlen(split[0])
			&& ft_strncmp(curr->name, split[0], ft_strlen(curr->name)) == 0)
			break;
		curr = curr->next;
	}
	if (curr)
	{
		free(curr->value);
		curr->value = NULL;
		if (split[1])
			curr->value = ft_strdup(split[1]);
		return;
	}
	// if (curr)
	// {
	// 	curr->value = split[1];
	// 	return ;
	// }
	new = gc_malloc(shell, sizeof(t_env));
	new->name = ft_strdup(split[0]);
	gc_add(shell, new->name);
	new->value = NULL;
	if (split[1])
	{
		new->value = ft_strdup(split[1]);
		gc_add(shell, new->value);
	}
	new->next = *env;
	*env = new;
}

// removes variable in shell
void	unset(t_env **env, char *rm_var)
{
	t_env	*curr;
	t_env	*prev;

	if (!rm_var)
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

