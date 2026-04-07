/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:11:42 by olmatske          #+#    #+#             */
/*   Updated: 2026/04/07 10:01:30 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include "./libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_redir {
	// types of redirection     OUT (enum)
	// target                   text.txt
}	t_redir;

// typedef struct s_built_in {
	
// }	t_built_in;

typedef enum e_builtin {
	NONE,
	ECHO,
	ECHO_N,
	PWD,
	EXIT,
	ENV,
	CD,
	EXPORT,
	UNSET

}	t_builtin;

// typedef s_redirection {
// 	char *target;
// }	t_redirection

typedef struct s_cmd {
	char		**args; // args[0] = "cat" -> args[1] = main.c
	// t_redir		*redir; 
	t_builtin	builtin;		//built_in; // nothing because cat isn't a built in function
}	t_cmd;

typedef struct s_cmd_node {
	t_cmd				*cmd;
	struct s_cmd_node	*next;
}	t_cmd_node;


// int		main(int argc, char **argv, char **envp);


////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS ///////////////////////////////////////////////////////////////////
int main(int argc, char **argv, char **envp);
// builtin.c ///////////////////////////////////////////////////////////////////

int wrapper_builtin(t_cmd cmd, char **envp);
void echo(char *str);
void echo_n(char *str);
void pwd(void);
void ft_exit(void);
void env(char **envp);
void cd(char *path);
void export(char **envp, char *new_var);
void unset(char **envp, char *rm_var);





#endif


// cat main.c > text.txt
