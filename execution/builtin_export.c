/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 11:05:12 by olmatske          #+#    #+#             */
/*   Updated: 2026/06/02 21:31:55 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	swap_array(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	sort_array(char **str)
{
	int	swapped;
	int	i;

	if (!str)
		return ;
	swapped = 1;
	i = 0;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (str[i] && str[i + 1])
		{
			if (ft_strcmp(str[i], str[i + 1]) > 0)
			{
				swap_array(&str[i], &str[i + 1]);
				swapped = 1;
			}
			i++;
		}
	}
}

void	print_export(char **arr)
{
	int	i;

	if (!arr)
		return ;
	sort_array(arr);
	i = 0;
	while (arr[i])
	{
		if (!ft_strncmp(arr[i], "?=", 2))
			i++;
		printf("declare -x %s\n", arr[i]);
		i++;
	}
	free_env_array(arr);
}
