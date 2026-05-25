/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:09:53 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/22 10:00:09 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void wrapper(char **argv, t_cmd *cmd)
{
	if (cmd->redir->out_type == OUT_NONE)
		input(open(argv[1], O_RDONLY));
	else if (cmd->redir->out_type == OUT_OVERWRITE)
		overwrite(argv);
	else if (cmd->redir->out_type == OUT_APPEND)
		append(argv);
}

int create_file(char *filename)
{
	int		fd;
	
	fd = open(filename, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	if (close(fd) < 0)
	{
		perror("close");
		return (1);
	}
	return (0);
}

// cat < file.txt outputs file content to shell
void input(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line == NULL)
		{
			perror("Error:");
			return;
		}
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
}

void overwrite(char **argv)
{
	int fd;
	char *text;

	text = readline("");

	fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, text, ft_strlen(text));
}

void append(char **argv)
{
	int fd;
	char *text;

	text = readline("");
	fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0644);

	write(fd, text, ft_strlen(text));
}
