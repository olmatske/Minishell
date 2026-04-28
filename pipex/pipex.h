/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:59:24 by anshuval          #+#    #+#             */
/*   Updated: 2026/01/19 22:01:38 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>

int		main(int argc, char **argv, char **envp);
void	validate(int argc);
void	ft_free_array(char **to_free);
void	ft_error(char *s, int exit_code);
void	ft_perror(char *s);
void	child_process_cmd1(char *cmd, char *file, char **envp, int pipe_fd[2]);
void	child_process_cmd2(char *cmd, char *file, char **envp, int pipe_fd[2]);
char	*find_command_path(char *cmd, char **envp);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);

#endif
