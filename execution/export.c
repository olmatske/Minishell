/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 11:05:12 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/13 11:08:04 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_strcmp(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}

static void	swap_env_contents(t_env *a, t_env *b)
{
	char *tmp_name = a->name;
	char *tmp_value = a->value;

	a->name = b->name;
	a->value = b->value;
	b->name = tmp_name;
	b->value = tmp_value;
}

// soprt env list alpahbetically and only print declare -x + varables
static void	sort_env(t_env *env)
{
	int swapped;
	t_env *curr;
	t_env *end = NULL;

	if (!env)
		return;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		curr = env;
		while (curr->next != end)
		{
			if (ft_strcmp(curr->name, curr->next->name) > 0)
			{
				swap_env_contents(curr, curr->next);
				swapped = 1;
			}
			curr = curr->next;
		}
		end = curr;
	}
}

void	print_export(t_env *env)
{
	t_env	*curr;

	sort_env(env);
	curr = env;
	curr = curr->next;
	while (curr)
	{
		if (curr->value == NULL)
			printf("declare -x %s=\n", curr->name);
		else
			printf("declare -x %s=\"%s\"\n", curr->name, curr->value);
		curr = curr->next;
	}
}
