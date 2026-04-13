/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:09:53 by olmatske          #+#    #+#             */
/*   Updated: 2026/04/13 18:28:36 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	input(int fd);

int main(int argc, char **argv)
{
	char	*file_name;
	int		fd;

	if (argc != 2)
	{
		printf("not enough arguments", argv[0]);
		return (1);
	}
	file_name = argv[1];
	fd = open(file_name, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	input(fd);
	if (close(fd) < 0)
	{
		perror("close");
		return (1);
	}
	return (0);
}
// open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644)
void input(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
}


