/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 11:05:12 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/13 11:08:04 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	swap_array(char **a, char **b)
{
	char *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	sort_array(char **str)
{
	int	swapped;
	int	i;

	if (!str)
		return;
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
		printf("declare -x %s\n", arr[i]);
		i++;
	}
	free_env_array(arr);
}
////////////////////////////////////////////////////////////////////////////////

void	update_var(t_env **env, char *name, char *value)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->name, name) == 0)
		{
			free(curr->value);
			if (value)
				curr->value = ft_strdup(value);
			else
				curr->value = NULL;
			return ;
		}
		curr = curr->next;
	}
}

void	append_var(t_env **env, char *name, char *value)
{
	t_env	*curr;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	if (*env == NULL)
		*env = new;
	else
	{
		curr = *env;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

// returns 1 if the variable is present, 0 if it is not
int	check_var(t_env *env, char *var)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (ft_strcmp(curr->name, var) == 0)
			return (1);
		curr = curr->next;
	}
	return (0);
}
