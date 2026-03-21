/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:33:42 by anshuval          #+#    #+#             */
/*   Updated: 2026/02/26 21:11:17 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*copied_env;

	(void)argv;
	if (argc != 1)
	{
		printf("Minishell does not accept arguments. Type in only ./Minishell\n");
		return (1);
	}
	copied_env = shell_env(envp);
	while (1)
	{
		line = readline("Minishell$");
		if (line != NULL)
			add_history(line);
		main_parsing(line);
		shell_loop(copied_env);
	}
	return (0);
}
