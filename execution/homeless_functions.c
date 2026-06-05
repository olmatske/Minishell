/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   homeless_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:28:33 by olmatske          #+#    #+#             */
/*   Updated: 2026/06/05 14:20:00 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

t_pipex	*pipex_init(t_shell *shell, t_cmd_node *cmd_list)
{
	t_pipex	*p;

	p = gc_malloc(shell, sizeof(t_pipex));
	p->curr = cmd_list;
	p->head = cmd_list;
	p->shell = shell;
	p->cmd_count = pipe_count(cmd_list);
	p->pids = gc_malloc(shell, sizeof(pid_t) * p->cmd_count);
	p->pipe_fd[0] = -1;
	p->pipe_fd[1] = -1;
	p->i = 0;
	p->prev_read = -1;
	return (p);
}

char	*expand_tilde(char *arg, t_env *env)
{
	char	*home;

	if (!arg || arg[0] != '~')
		return (ft_strdup(arg));
	if (arg[1] && arg[1] != '/')
		return (ft_strdup(arg));
	home = NULL;
	if (!check_var(env, "HOME"))
		return (NULL);
	home = get_value(env, "HOME");
	home = ft_strjoin(home, arg + 1);
	if (!home)
		return (NULL);
	return (home);
}

void	ft_puterr(char *s1, char *s2, char *s3)
{
	write(STDERR_FILENO, C_RED, ft_strlen(C_RED));
	write(STDERR_FILENO, M, ft_strlen(M));
	write(STDERR_FILENO, ": ", 2);
	if (s1)
		write(STDERR_FILENO, s1, ft_strlen(s1));
	if (s2)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, s2, ft_strlen(s2));
	}
	if (s3)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, s3, ft_strlen(s3));
	}
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, R, ft_strlen(R));
}
