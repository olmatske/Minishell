/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:52:51 by olmatske          #+#    #+#             */
/*   Updated: 2026/04/13 16:46:52 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_cmd cmd;
	char *str[] = {"MYVAR", NULL};
	cmd.args = str;
	cmd.builtin = UNSET;

	wrapper_builtin(cmd, envp);
	return (0);
}

//  t_cmd *cmd, t_env *env, t_shell *sh
int wrapper_builtin(t_cmd cmd, char **envp)
{
	if (cmd.builtin == NONE)
		return (1);
	else if (cmd.builtin == ECHO)
		echo(readline("$ "));                   // put away
	else if (cmd.builtin == ECHO_N)
		echo_n(readline("$ "));                 // puy away
	else if (cmd.builtin == PWD)
		pwd();
	else if (cmd.builtin == EXIT)
		ft_exit();
	else if (cmd.builtin == ENV)
		env(envp);
	else if (cmd.builtin == CD)
		cd(cmd.args[0]);
	else if (cmd.builtin == EXPORT)
		export(envp, *cmd.args);
	else if (cmd.builtin == UNSET)
		unset(envp, *cmd.args);
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
// supposed to update the env in shell
void export(char **envp, char *new_var)
{
	int i = 0;
	char *new_env_var = ft_strdup(new_var);

	while (envp[i])
		i++;
	envp[i] = new_env_var;
	envp[i + 1] = NULL;
}
// supposed to update the env in shell
void unset(char **envp, char *rm_var)
{
	export(envp, "MYVAR=Helloo"); // remove later!!
	int i = 0;
	int len = ft_strlen(rm_var);

	while (envp[i])
	{
		if (!ft_strncmp(envp[i], rm_var, len) && envp[i][len] == '=')
		{
			free(envp[i]);
			while (envp[i])
			{
				envp[i] = envp[i + 1];
				i++;
			}
			printf("Successful removal\n"); // remove later!!
			return;
		}
		i++;
	}
	perror("Error");
}

