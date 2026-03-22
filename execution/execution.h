/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:11:42 by olmatske          #+#    #+#             */
/*   Updated: 2026/03/22 17:56:14 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_redir {
	// types of redirection     OUT (enum)
	// target                   text.txt
}	t_redir;

typedef struct s_built_in {
	
}	t_built_in;

typedef struct s_cmd {
	char		**args; // args[0] = "cat" -> args[1] = main.c
	t_redir		*redir; 
	t_built_in	built_in; // nothing because cat isn't a built in function
}	t_cmd;

typedef struct s_cmd_node {
	t_cmd				*cmd;
	struct s_cmd_node	*next;
}	t_cmd_node;


// int		main(int argc, char **argv, char **envp);

#endif


// cat main.c > text.txt
