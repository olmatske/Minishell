/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:52:51 by olmatske          #+#    #+#             */
/*   Updated: 2026/03/22 19:13:25 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int main(void)
{
	if (echo() != 0)
		return (printf("error\n"), 1);
	return (0);
}

int echo()
{
	char *str;
	char *builtin = "echo";
	int	i = 0;

	str = readline("$ ");
	while (str[i] == builtin[i])
		i++;
	if (i < 4)
		return (printf("error\n"), 1);
	i += 1;
	while (str[i])
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\n");
	return (0);
}

