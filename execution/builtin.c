/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:52:51 by olmatske          #+#    #+#             */
/*   Updated: 2026/04/05 17:24:28 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int main(void)
{
	t_cmd cmd;
	char *str[] = {"Hello World", NULL};
	cmd.args = str;
	cmd.builtin = ECHO_N;

	while (1)
		wrapper_builtin(cmd);
	return (0);
}

//  t_cmd *cmd, t_env *env, t_shell *sh
int wrapper_builtin(t_cmd cmd)
{
	if (cmd.builtin == NONE)
		return (1);
	else if (cmd.builtin == ECHO)
		echo(readline("$ "));
	else if (cmd.builtin == ECHO_N)
		echo_n(readline("$ "));
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
