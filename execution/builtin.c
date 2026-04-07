/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:52:51 by olmatske          #+#    #+#             */
/*   Updated: 2026/04/07 09:52:05 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_cmd cmd;
	char *str[] = {"..", NULL};
	cmd.args = str;
	cmd.builtin = CD;

	wrapper_builtin(cmd, envp);
	return (0);
}

//  t_cmd *cmd, t_env *env, t_shell *sh
int wrapper_builtin(t_cmd cmd, char **envp)
{
	if (cmd.builtin == NONE)
		return (1);
	else if (cmd.builtin == ECHO)
		echo(readline("$ "));
	else if (cmd.builtin == ECHO_N)
		echo_n(readline("$ "));
	else if (cmd.builtin == PWD)
		pwd();
	else if (cmd.builtin == EXIT)
		ft_exit();
	else if (cmd.builtin == ENV)
		env(envp);
	else if (cmd.builtin == CD)
		cd(cmd.args[0]);
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
void env(char **envp)
{
	int	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
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