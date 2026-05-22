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

static void	swap_array(char **a, char **b)
{
	char *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// soprt env list alpahbetically and only print declare -x + varables
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

void	update_variable(t_shell *shell, t_env **env, char *name, char *value)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->name, name) == 0)
		{
			free(curr->value);
			if (value)
				curr->value = gc_strdup(shell, value);
			else
				curr->value = NULL;
			return ;
		}
		curr = curr->next;
	}
}

void	append_variable(t_env **env, char *name, char *value)
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

// does arg have a value?
//	  > no -> does arg have '='?
//			> no -> don't print in env, print in export "declare -x TEST"
//			> yes -> print in both: 'TEST=' + 'declare -x TEST=""'
//	  > yes -> does the variable already exist?
//			> no -> create and append to env list
//			> yes -> update the variable
// update smth, I forgot what 


// does variable name exist?
//		> yes -> does it have an equal sign?
//				> yes -> replace with value
//				> no  -> replace with NULL
//		> no  -> does it have an equal sign?
//				> yes -> append to env list with value
//				> no  -> append to env list with NULL
//
//
//
//
// static void	swap_env_contents(char *a, char *b)
// {
// 	char *tmp;

// 	tmp = a;
// 	a = b;
// 	b = tmp;
// }

// // soprt env list alpahbetically and only print declare -x + varables
// static void	sort_array(char **env)
// {
// 	int	i;
// 	int	swapped;

// 	if (!env)
// 		return;
// 	i = 0;
// 	swapped = 1;
// 	while (swapped)
// 	{
// 		swapped = 0;
// 		while (env[i] && env[i + 1])
// 		{
// 			if (ft_strcmp(env[i], env[i + 1]) > 0)
// 			{
// 				swap_env_contents(env[i], env[i + 1]);
// 				swapped = 1;
// 			}
// 			i++;
// 		}
// 	}
// }

// void	print_export(char **env)
// {
// 	int	i;

// 	i = 0;
// 	sort_array(env);
// 	while (env[i])
// 	{
// 		if (ft_strcmp(env[i], "?=0") == 0)
// 		{
// 			i++;
// 			continue;
// 		}
// 		if (curr->value == NULL)
// 			printf("declare -x %s\n", curr->name);
// 		else
// 			printf("declare -x %s=\"%s\"\n", curr->name, curr->value);
// 		curr = curr->next;
// 	}
// }
