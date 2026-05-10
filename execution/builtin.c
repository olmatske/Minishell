/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:52:51 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/10 12:35:47 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	t_cmd cmd;
// 	char *str[] = {"MYVAR", NULL};
// 	cmd.args = str;
// 	cmd.builtin = UNSET;

// 	wrapper_builtin(cmd, envp);
// 	return (0);
// }

//  t_cmd *cmd, t_env *env, t_shell *sh
int wrapper_builtin(t_shell *shell, t_cmd *cmd, t_env *env)
{
	if (cmd->builtin == NONE_B)
		return (1);
	else if (cmd->builtin == ECHO)
		echo(readline("$ "));                   // put away
	else if (cmd->builtin == ECHO_N)
		echo_n(readline("$ "));                 // puy away
	else if (cmd->builtin == PWD)
		pwd();
	else if (cmd->builtin == EXIT)
		ft_exit();
	else if (cmd->builtin == ENV)
		ft_env(env);
	else if (cmd->builtin == CD)
		cd(cmd->args[0]);
	else if (cmd->builtin == EXPORT)
		export(shell, env, ft_split(*cmd->args, '='));
	else if (cmd->builtin == UNSET)
		unset(&env, *cmd->args);
	return (0);
}

void echo(char *str)
{
	printf("%s\n", str);
}

void echo_n(char *str)
{
	printf("%s", str);
}
void pwd(void)
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
void ft_exit(void)
{
	printf("exit\n");
	exit(0);
}
void ft_env(t_env *env)
{
	t_env *curr;

	curr = env;
	while (curr->next)
	{
		printf("%s%s\n", curr->name, curr->value);
		curr = curr->next;
	}
}

void cd(char *path)
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
void export(t_shell *shell, t_env *env, char **split)
{
	t_env	*curr;
	t_env	*new;

	new = gc_malloc(shell, sizeof(t_env));
	curr = env;
	while (curr->next)
		curr = curr->next;
	new->name = split[0];
	new->value = split[1];
	new->next = NULL;
	curr->next = new;
}

// removes variable in shell
void unset(t_env **env, char *rm_var)
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

