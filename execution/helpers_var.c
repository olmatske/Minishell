/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 09:43:40 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/29 09:44:59 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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