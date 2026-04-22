/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:41:47 by olmatske          #+#    #+#             */
/*   Updated: 2026/04/20 17:17:34 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int main(int argc, char **argv, char **envp)
{
	(void)envp;
	(void)argc;
	(void)argv;

	t_cmd	cmd;
	char	*path = NULL;
	char	*str[] = {"ls", "-l", NULL};
	int		id;

	cmd.args = str;
	cmd.builtin = UNSET;

	int i = 0;
	if (!access(str[0], X_OK));
	{
		id = fork();
		if (id == 0)
			execve()
	}
	
	return (0);
}



// Resolve the path.

// Check it with access(path, X_OK) or access(path, F_OK) depending on what you want to know.

// If it passes, fork().

// In the child, call execve().

// In the parent, waitpid().