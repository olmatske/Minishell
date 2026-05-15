/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:41:29 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/15 20:09:20 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	echo_n_check(char **str)
{
	int	i;
	int	k;
	int	found;

	i = 1;
	k = 0;
	found = 0;
	while (str[i])
	{
		if (str[i][0] != '-')
			break;
		k = 1;
		while (str[i][k] == 'n')
			k++;
		if (str[i][k] == '\0')
		{
			i++;
			found = 1;
		}
		else
			break;
	}
	return (found);
}

void	echo(char **str)
{
	int	i;
	int	n;

	i = 1;
	n = echo_n_check(str);
	if (n)
		i = 2;
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
}
