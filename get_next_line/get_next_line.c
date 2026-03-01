/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:20:37 by anshuval          #+#    #+#             */
/*   Updated: 2025/09/04 12:14:39 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	ft_buffer_is_empty(int fd, char *buffer, char *line)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		buffer[0] = '\0';
		free (line);
		return (-1);
	}
	if (bytes_read == 0)
		return (0);
	buffer[bytes_read] = '\0';
	return (bytes_read);
}

static char	*ft_end_of_line_not_found(char *line, char *buffer)
{
	size_t		line_len;
	size_t		chunk_len;
	char		*new_line;

	line_len = ft_strlen(line);
	chunk_len = ft_strlen(buffer);
	new_line = malloc(line_len + chunk_len + 1);
	if (new_line == NULL)
		return (NULL);
	if (line != NULL)
		ft_memcpy(new_line, line, line_len);
	ft_memcpy(&new_line[line_len], buffer, chunk_len);
	new_line[line_len + chunk_len] = '\0';
	return (new_line);
}

static char	*ft_end_of_line_found(char *line, char *end_of_line, char *buffer)
{
	size_t		line_len;
	size_t		chunk_len;
	char		*new_line;

	line_len = ft_strlen(line);
	chunk_len = end_of_line - buffer + 1;
	new_line = malloc(line_len + chunk_len + 1);
	if (new_line == NULL)
		return (NULL);
	if (line != NULL)
		ft_memcpy(new_line, line, line_len);
	ft_memcpy(&new_line[line_len], buffer, chunk_len);
	new_line[line_len + chunk_len] = '\0';
	ft_memmove (buffer, end_of_line + 1, ft_strlen(end_of_line + 1) + 1);
	return (new_line);
}

static char	*ft_end_of_line(char *buffer, char *line, size_t *line_ready)
{
	char		*end_of_line;
	char		*new_line;

	*line_ready = 0;
	end_of_line = ft_strchr(buffer, '\n');
	if (end_of_line != NULL)
	{
		new_line = ft_end_of_line_found(line, end_of_line, buffer);
		if (new_line == NULL)
			return (free (line), NULL);
		free(line);
		*line_ready = 1;
		return (new_line);
	}
	else
	{
		new_line = ft_end_of_line_not_found(line, buffer);
		if (new_line == NULL)
			return (free (line), NULL);
		free(line);
		buffer[0] = '\0';
		return (new_line);
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;
	size_t		line_ready;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	while (1)
	{
		if (buffer[0] == '\0')
		{
			bytes_read = ft_buffer_is_empty(fd, buffer, line);
			if (bytes_read < 0)
				return (NULL);
			if (bytes_read == 0)
				break ;
		}
		line = ft_end_of_line(buffer, line, &line_ready);
		if (line_ready == 1)
			return (line);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>

// int main(void)
// {
// 	int fd;
// 	char *line;
// 	fd = open("test.txt", O_RDWR);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if(!line)
// 		{
// 			printf("ptr %p\n", line);
// 			break;
// 		}
// 		printf("[NEWLINE]>%s", line);
// 		free (line);
// 	}
// 	close (fd);
// 	return 0;
// }