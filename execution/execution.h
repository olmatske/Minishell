/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:11:42 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/26 09:55:53 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define C	"Command not found\n"
# define M	"Minishell:"
# define I	"not a valid identifier"
# define A	"too many arguments"
# define FD	"No such file or directory"
# define N	"numeric argument required"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include "../minishell.h"

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS ///////////////////////////////////////////////////////////////////

// int main(int argc, char **argv);
int main(int argc, char **argv, char **envp);


// builtin.c ///////////////////////////////////////////////////////////////////
int		wrapper_builtin(t_shell *shell, t_cmd_node *cmd_node, t_env **env);
int		echo(char **str);
int		pwd(void);
int		ft_exit(t_shell *shell, t_env **env, t_cmd_node *cmd);
int		ft_env(t_env **env);
int		cd(char **path, t_env *env, t_shell *shell);
int		export(t_shell *shell, t_env **env, char *arg, char **split);
int		unset(t_env **env, char *rm_var);

// executor.c //////////////////////////////////////////////////////////////////
int		exec_pipeline(t_shell *shell, t_cmd_node *cmd_list);

// externals.c /////////////////////////////////////////////////////////////////
int		exec_external(t_shell *shell, t_cmd *cmd, t_env *env);
void	exec_external_child(t_shell *shell, t_cmd *cmd, t_env *env);
void	free_split(char **str);

// garbage_collector.c /////////////////////////////////////////////////////////
void	*gc_malloc(t_shell *shell, size_t size);
void	*gc_calloc(t_shell *shell, size_t count, size_t size);
int		gc_add(t_shell *shell, void *ptr);
void	gc_single_free(t_shell *shell, void *ptr);
void	gc_free_all(t_shell *shell);

// orchestrator /////////////////////////////////////////////////////////////////
int		shell_loop(t_shell *shell, t_cmd_node *cmd_list);
int		exec_single_cmd(t_shell *shell, t_env *environment, t_cmd_node *cmd_list);
void	free_all(t_shell *shell, t_env **env, t_cmd_node *cmd);

// pipe_helpers.c //////////////////////////////////////////////////////////////
int		open_file(char *file, int mode);
int		pipe_count(t_cmd_node *cmd_list);
void	redirect_input(int fd);
void	redirect_output(int fd);
int		execution(t_shell *shell, t_cmd_node *cmd, t_env **env);

// redirections.c ////////////////////////////////////////////////////////////////
int		wrapper_redirections(t_redir *redir);
// int		create_file(char *filename);
// void	input(int fd);
// void	overwrite(char **text);
// void	append(char **argv);

// export.c /////////////////////////////////////////////////////////////////////
void	append_variable(t_env **env, char *name, char *value);
void	print_export(char **arr);
int		check_var(t_env *env, char *var);
void	update_variable(t_env **env, char *name, char *value);
char	**env_array_for_export(t_env *env);

// builtin_echo.c //////////////////////////////////////////////////////////////
int		echo(char **str);

// checkers.c //////////////////////////////////////////////////////////////////
int		check_export(char *str);

int		ft_strcmp(char *a, char *b);
int		isnumstr(const char *str);
t_env	*copy_of_env(t_env *env);
void	free_env_list(t_env **head);

char	*gc_strdup(t_shell *shell, const char *s1);
char	*gc_strjoin(t_shell *shell, char const *s1, char const *s2);

#endif







// typedef enum e_out_type {
// 	IN_FILE,
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
