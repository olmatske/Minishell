/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:11:42 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/08 13:34:05 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include <stdlib.h>
#include "./libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./get_next_line/get_next_line.h"
#include <sys/types.h>
#include <sys/wait.h>

typedef enum e_builtin {
	NONE_B,
	ECHO,
	ECHO_N,
	PWD,
	EXIT,
	ENV,
	CD,
	EXPORT,
	UNSET

}	t_builtin;

typedef enum e_redir_type {
	NONE_R,
	INPUT,
	OVERWRITE,
	HEREDOC,
	APPEND
}	t_redir_type;


typedef struct s_pre_zero {
	void *ptr;
	struct s_pre_zero *next;
}	pre_zero;

typedef struct s_redir {
	char		*infile;                  // filename
	char		*heredoc_delimiter;
	char		*outfile;                 // filename
	t_redir_type	redir_type;
}	t_redir;

typedef struct s_env {
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

// shell struct will have a gc variable
typedef struct s_shell {
	t_env	**env;
	pre_zero *gc;
	int		exit;
}	t_shell;

typedef struct s_cmd {
	char			**args;
	t_redir			*redir; 
	t_redir_type	type_redir;
	t_builtin		builtin;
}	t_cmd;

typedef struct s_cmd_node {
	t_cmd				*cmd;
	struct s_cmd_node	*next;
}	t_cmd_node;

typedef struct s_pipex {
	t_cmd_node	*curr;
	t_shell		*shell;
	pid_t		*pids;
	int			i;
	int			cmd_count;
	int			pipe_fd[2];	// pipe_fd[0] read - pipde_fd[1] write
	int			prev_read;
}	t_pipex;




// int		main(int argc, char **argv, char **envp);


////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS ///////////////////////////////////////////////////////////////////

// int main(int argc, char **argv);
int main(int argc, char **argv, char **envp);


// builtin.c ///////////////////////////////////////////////////////////////////

int wrapper_builtin(t_cmd *cmd, char **envp);
void	echo(char *str);
void	echo_n(char *str);
void	pwd(void);
void	ft_exit(void);
void	env(char **envp);
void	cd(char *path);
void	export(char **envp, char *new_var);
void	unset(char **envp, char *rm_var);


// files.c /////////////////////////////////////////////////////////////////////

// int main(int argc, char **argv);
void	wrapper(char **argv, t_cmd cmd);
int		create_file(char *filename);
void	input(int fd);
void	overwrite(char **text);
void	append(char **argv);

// garbage_collector.c /////////////////////////////////////////////////////////
void	*gc_malloc(t_shell *shell, size_t size);
void	*gc_calloc(t_shell *shell, int count, size_t size);
int		gc_add(t_shell *shell, void *ptr);
int		gc_add(t_shell *shell, void *ptr);
void	gc_single_free(t_shell *shell, void *ptr);
void	gc_free_all(t_shell *shell);

// executor.c //////////////////////////////////////////////////////////////////
int		exec_pipeline(t_shell *shell, t_cmd_node *cmd_list);

// pipe_helpers.c //////////////////////////////////////////////////////////////
int		open_file(char *file, int mode);
int		pipe_count(t_cmd_node *cmd_list);
void	redirect_input(int fd);
void	redirect_output(int fd);

// void	execute_piped_cmd(char *cmd, char **envp);
int		open_file(char *file, int mode);
int		pipe_count(t_cmd_node *cmd_list);
void	redirect_input(int fd);
void	redirect_output(int fd);

void	execution(t_cmd *cmd, t_env **env);

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
