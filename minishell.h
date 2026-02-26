/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:30:44 by anshuval          #+#    #+#             */
/*   Updated: 2026/02/26 16:23:21 by anshuval         ###   ########.fr       */
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
	
} t_redir;

typedef struct s_built_in {
	
} t_built_in;

typedef struct s_cmd {
	char		**args;
	t_redir		*redir;
	t_built_in	built_in;
} t_cmd;

typedef struct s_cmd_node {
	t_cmd				*cmd;
	struct s_cmd_node	*next;
} t_cmd_node;


int		main(int argc, char **argv, char **envp);

#endif