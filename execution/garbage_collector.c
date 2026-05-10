/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:32:56 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/08 16:21:09 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// valgrind --leak-check=full ./minishell

void *gc_malloc(t_shell *shell, size_t size) // size used with sizeof(xyz)
{
	void *ptr;

	ptr = malloc(size);
	if (!shell)
		exit(1);
	if (!ptr)
	{
		gc_free_all(shell);
		exit(1);
	}
	if (gc_add(shell, ptr) != 0)
	{
		free(ptr);
		gc_free_all(shell);
		exit(1);
	}
	return(ptr);
}

void *gc_calloc(t_shell *shell, size_t count, size_t size) // size used with sizeof(xyz) - count is how much you need
{
	void *ptr;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	ptr = gc_malloc(shell, count * size);
	if (ptr)
		ft_memset(ptr, 0, count * size);
	return (ptr);
}

int gc_add(t_shell *shell, void *ptr)
{
	pre_zero *new;

	new = malloc(sizeof(pre_zero));
	if (!new)
		return (-1);
	new->ptr = ptr;
	new->next = shell->gc;
	shell->gc = new;
	return (0);
}

void gc_single_free(t_shell *shell, void *ptr)
{
	pre_zero	*curr;
	pre_zero	*prev;

	curr = shell->gc;
	prev = NULL;
	while (curr && curr->ptr != ptr)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return;
	if (prev)
		prev->next = curr->next;
	else
		shell->gc = curr->next;
	free(curr->ptr);
	free(curr);
}

void gc_free_all(t_shell *shell)
{
	pre_zero	*curr;
	pre_zero	*kill;

	if (!shell)
		return;
	kill = shell->gc;
	while (kill)
	{
		curr = kill->next;
		free(kill->ptr);
		free(kill);
		kill = curr;
	}
	shell->gc = NULL;
}
