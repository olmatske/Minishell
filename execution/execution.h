/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:11:42 by olmatske          #+#    #+#             */
/*   Updated: 2026/06/05 14:20:59 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define PATHLEN	4096

# define C	"command not found\n"
# define M	"Bashtard:"
# define I	"not a valid identifier"
# define A	"too many arguments"
# define FD	"No such file or directory"
# define N	"numeric argument required"
# define F	"fork failure"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "../minishell.h"

// FUNCTIONS ///////////////////////////////////////////////////////////////////

// builtin_export.c ////////////////////////////////////////////////////////////
void		print_export(char **arr);

// builtins_1.c ////////////////////////////////////////////////////////////////
int			ft_env(t_env **env);
int			export(t_shell *shell, t_env **env, char *arg, char **split);
int			unset(t_env **env, char *rm_var);

// builtins_2.c ////////////////////////////////////////////////////////////////
int			ft_exit(t_shell *shell, t_env **env, t_cmd_node *cmd);
int			echo(char **str);
int			cd(char **path, t_env *env, t_shell *shell);
int			pwd(void);

// checkers.c //////////////////////////////////////////////////////////////////
int			check_export(char *str);
void		update_shell_status(t_env **env, t_shell *shell);
void		update_pwd(t_env **env, char *new_path, char *old_path);
int			echo_n_check(char **str);

// pipes.c //////////////////////////////////////////////////////////////////
void		child_loop(int i, int cmd_count, int *pipe_fd, int prev_read);
void		parent_loop(int i, int cmd_count, int *pipe_fd, int *prev_read);
int			pipe_loop(t_pipex *p);
int			wait_pipeline(t_shell *shell, t_pipex *p);
int			exec_pipeline(t_shell *shell, t_cmd_node *cmd_list);

// externals.c /////////////////////////////////////////////////////////////////
int			exec_external(t_shell *shell, t_cmd *cmd, t_env *env);
int			handle_abortion(int status);

// garbage_collector.c /////////////////////////////////////////////////////////
void		*gc_malloc(t_shell *shell, size_t size);
void		*gc_calloc(t_shell *shell, size_t count, size_t size);
int			gc_add(t_shell *shell, void *ptr);
void		gc_single_free(t_shell *shell, void *ptr);
void		gc_free_all(t_shell *shell);

// orchestrator ////////////////////////////////////////////////////////////////
int			shell_loop(t_shell *shell, t_cmd_node *cmd_list);
int			exec_single_cmd(t_shell *shell, t_env *env, t_cmd_node *cmd_list);
void		free_all(int freenv, t_shell *shell, t_env **env, t_cmd_node *cmd);

// pipe_helpers.c //////////////////////////////////////////////////////////////
int			open_file(char *file, int mode);
int			pipe_count(t_cmd_node *cmd_list);
void		redirect_input(int fd);
void		redirect_output(int fd);
int			execution(t_shell *shell, t_cmd_node *cmd, t_env **env);

// helpers_var.c ///////////////////////////////////////////////////////////////
void		update_var(t_env **env, char *name, char *value);
void		append_var(t_env **env, char *name, char *value);
int			check_var(t_env *env, char *var);
char		*get_value(t_env *env, char *var);

// helpers.c ///////////////////////////////////////////////////////////////////
int			ft_strcmp(char *a, char *b);
char		*gc_strdup(t_shell *shell, const char *s1);
char		*gc_strjoin(t_shell *shell, char const *s1, char const *s2);
int			isnumstr(const char *str);
void		free_all(int free_env, t_shell *shell,
				t_env **env, t_cmd_node *cmd);

// homeless_functions.c ////////////////////////////////////////////////////////
void		free_split(char **str);
t_pipex		*pipex_init(t_shell *shell, t_cmd_node *cmd_list);
char		*expand_tilde(char *arg, t_env *env);
void		ft_puterr(char *s1, char *s2, char *s3);

// orchestrator.c //////////////////////////////////////////////////////////////
int			shell_loop(t_shell *shell, t_cmd_node *cmd_list);

// redirections.c //////////////////////////////////////////////////////////////
int			wrapper_redirections(t_redir *redir);

// paths.c /////////////////////////////////////////////////////////////////////
int			decide_path(t_cmd *cmd);
char		*get_path_value(char **env);
char		*join_path(t_shell *shell, char *dir, char *cmd);
char		*resolve_path(t_shell *shell, t_cmd *cmd, char **env);

// pipe_helpers.c //////////////////////////////////////////////////////////////
int			open_file(char *file, int mode);
int			pipe_count(t_cmd_node *cmd_list);
void		redirect_input(int fd);
void		redirect_output(int fd);
int			execution(t_shell *shell, t_cmd_node *cmd, t_env **env);

// redirections.c //////////////////////////////////////////////////////////////
int			wrapper_redirections(t_redir *r);

// wrappers.c //////////////////////////////////////////////////////////////////
int			wrapper_builtins(t_shell *shell, t_cmd_node *cmd_node, t_env **env);
int			wrapper_all(t_shell *shell, t_cmd_node *n, t_env **env, int exit);

#endif
