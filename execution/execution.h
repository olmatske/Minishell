/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:11:42 by olmatske          #+#    #+#             */
/*   Updated: 2026/04/13 17:28:54 by olmatske         ###   ########.fr       */
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
#include "./get_next_line/get_next_line.h"

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

typedef enum e_out_type {
	OUT_NONE,
	OUT_APPEND,
	OUT_OVERWRITE
}	t_out_type;


typedef struct s_redir {
	char		*infile;                  // filename
	char		*heredoc_delimiter;
	char		*outfile;                 // filename
	t_out_type	out_type;
}	t_redir;


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

int main(int argc, char **argv);
// int main(int argc, char **argv, char **envp);


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







// typedef enum e_out_type {
// 	OUT_NONE,
// 	OUT_APPEND,
// 	OUT_OVERWRITE
// }	t_out_type;

// typedef struct s_redir {
// 	char		*infile;                  // filename
// 	char		*heredoc_delimiter;
// 	char		*outfile;                 // filename
// 	t_out_type	out_type;
// }	t_redir;

// typedef enum e_built_in_name {
// 	BUILTIN_NONE,
// 	BUILTIN_ECHO,
// 	BUILTIN_CD,
// 	BUILTIN_PWD,
// 	BUILTIN_EXPORT,
// 	BUILTIN_UNSET,
// 	BUILTIN_ENV,
// 	BUILTIN_EXIT
// }	t_built_in_name;

// typedef struct s_cmd {
// 	char			**args;
// 	t_redir			*redir;
// 	t_built_in_name	built_in_name;
// }	t_cmd;

// typedef struct s_cmd_node {
// 	t_cmd				*cmd;
// 	struct s_cmd_node	*next;
// }	t_cmd_node;

// typedef struct s_env {
// 	char			*name;
// 	char			*value;
// 	struct s_env	*next;
// }	t_env;











// cat main.c > text.txt
