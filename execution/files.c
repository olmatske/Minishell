/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:09:53 by olmatske          #+#    #+#             */
/*   Updated: 2026/04/08 19:45:13 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int main(int argc, char **argv)
{
	(void)argc;
	char *file_name = argv[1];
	int fd;
	// char *content = argv[2];
	fd = open(file_name, O_CREAT, O_RDWR);
	if (fd < 0)
		return (1);
	sleep(3);
	if (close(fd) < 0)
		return (1);
	return (0);
}
// open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644)
