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

void	print_export(t_env *copy)
{
	t_env	*curr;
	t_env	*tmp;

	sort_env(copy);
	curr = copy;
	while (curr)
	{
		if (!curr->name || ft_strcmp(curr->name, "?") == 0)
		{
			curr = curr->next;
			continue;
		}
		if (curr->value == NULL)
			printf("declare -x %s\n", curr->name);
		else
			printf("declare -x %s=\"%s\"\n", curr->name, curr->value);
		curr = curr->next;
	}
	while (copy)
	{
		tmp = copy;
		copy = copy->next;
		free(tmp);
	}
}
////////////////////////////////////////////////////////////////////////////////

void	update_variable(t_shell *shell, t_env **env, char *name, char *value)
{
	t_env	*curr;

	curr = *env;
	(void)shell;
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

void	append_variable(t_shell *shell, t_env **env, char *name, char *value)
{
	t_env	*curr;
	t_env	*new;

	new = gc_malloc(shell, sizeof(t_env));
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->next = NULL;
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
// static void	sort_env(char **env)
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
// 	sort_env(env);
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
