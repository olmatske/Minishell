/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:30:44 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/29 18:17:01 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "get_next_line/get_next_line.h"
# include "./libft/libft.h"
// # include "./execution/execution.h"

#ifdef __APPLE__
# ifndef rl_clear_history
#  define rl_clear_history clear_history
# endif
#endif

extern int	g_signal;

typedef enum e_out_type {
	IN_FILE, // -> input
	OUT_APPEND,
	OUT_OVERWRITE
}	t_out_type;

typedef struct s_redir {
	char			*infile;
	char			*heredoc_delimiter;
	char			*outfile;
	t_out_type		out_type;
	struct s_redir	*next;
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

////////////////////////////////////////////////////////////////////////////////

typedef struct s_pre_zero {
	void *ptr;
	struct s_pre_zero *next;
}	pre_zero;

typedef struct s_shell {
	t_env	**env;
	pre_zero *gc;
	int		exit;
}	t_shell;

typedef struct s_pipex {
	t_cmd_node	*curr;
	t_shell		*shell;
	pid_t		*pids;
	int			i;
	int			cmd_count;
	int			pipe_fd[2];	// pipe_fd[0] read - pipde_fd[1] write
	int			prev_read;
}	t_pipex;

////////////////////////////////////////////////////////////////////////////////

int			main(int argc, char **argv, char **envp);
t_env		*shell_env(char **envp);
t_cmd_node	*main_parsing(char *line, t_env *copied_env);
char		**env_array_for_execution(t_env *copied_env);
char		**env_array_without_value(t_env *copied_env);
char		**free_env_array(char **env_array);
void		ft_error(char *s, int exit_code);
void		ft_perror(char *s);
void		replace_signals(void);
int			is_it_space_only(char *line);
void		free_cmd_list(t_cmd_node *cmd_list);
void		free_env_list(t_env **head);
int			env_list_length(t_env *head);
char		*append_new_line(char *line, char *new_chunk);
void		just_copy(char *old_w, int *i, char **new_w);
void		expand_env(char *old_w, int *i, char **new_w, t_env *env);

////////////////////////////////////////////////////////////////////////////////
int			shell_loop(t_shell *shell, t_cmd_node *cmd_list);
void		free_all(t_shell *shell, t_env **env, t_cmd_node *cmd);
int			ft_strcmp(char *a, char *b);
void		update_shell_status(t_env **env, t_shell *shell);
////////////////////////////////////////////////////////////////////////////////
#endif
