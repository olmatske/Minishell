/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:30:44 by anshuval          #+#    #+#             */
/*   Updated: 2026/03/23 16:09:46 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "get_next_line/get_next_line.h"

// extern t_env	*copied_env;

typedef enum e_out_type {
	OUT_NONE,
	OUT_APPEND,
	OUT_OVERWRITE
}	t_out_type;

typedef struct s_redir {
	char		*infile;
	char		*heredoc_delimiter;
	char		*outfile;
	t_out_type	out_type;
}	t_redir;

typedef enum e_built_in_name {
	BUILTIN_NONE,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT
}	t_built_in_name;

typedef struct s_cmd {
	char			**args;
	t_redir			*redir;
	t_built_in_name	built_in_name;
}	t_cmd;

typedef struct s_cmd_node {
	t_cmd				*cmd;
	struct s_cmd_node	*next;
}	t_cmd_node;

typedef struct s_env {
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

int			main(int argc, char **argv, char **envp);
t_env		*shell_env(char **envp);
t_cmd_node	*main_parsing(char *line);
char		**env_array_for_execution(t_env *copied_env);
char		**free_env_array(char **env_array);
void		ft_error(char *s, int exit_code);
void		ft_perror(char *s);
void		free_cmd_list(t_cmd_node *cmd_list);
void		free_env_list(t_env **head);

#endif