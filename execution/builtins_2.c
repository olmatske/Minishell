/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:41:29 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/29 09:55:29 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	echo_n_check(char **str)
{
	int	i;
	int	k;
	int	found;

	i = 1;
	k = 0;
	found = 0;
	while (str[i])
	{
		if (str[i][0] != '-')
			break;
		k = 1;
		while (str[i][k] == 'n')
			k++;
		if (str[i][k] == '\0')
		{
			i++;
			found = 1;
		}
		else
			break;
	}
	return (found);
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
		fprintf(stderr, "%s cd: %s: %s\n", M, target, FD);
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
	t_env	*curr;
	char	*target;

	curr = env;
	if (!path || !path[0])
		return (1);
	if (path[1] && path[2])
		return (fprintf(stderr, "%s cd: %s\n", M, A), 1);
	target = path[1];
	if (!target || !ft_strcmp(target, "~"))
	{
		while (curr)
		{
			if (!ft_strcmp(curr->name, "HOME"))
			{
				target = curr->value;
				break;
			}
			curr = curr->next;
		}
		if (!target)
			fprintf(stderr, "%s HOME not set\n", M);
	}
	return (change_dir(shell, target));
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