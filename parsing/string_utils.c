/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 21:55:08 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/31 23:02:15 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*append_char(char *old_w, char c)
{
	char	*new_w;
	int		len;

	len = 0;
	if (old_w != NULL)
		len = ft_strlen(old_w);
	new_w = malloc(len + 2);
	if (new_w == NULL)
	{
		free(old_w);
		return (NULL);
	}
	if (old_w != NULL)
		ft_strlcpy(new_w, old_w, len + 1);
	new_w[len] = c;
	new_w[len + 1] = '\0';
	free(old_w);
	return (new_w);
}

char	*append_str(char *old_w, char *suffix)
{
	char	*new_w;

	if (suffix == NULL)
		return (old_w);
	if (old_w == NULL)
		return (ft_strdup(suffix));
	new_w = ft_strjoin(old_w, suffix);
	free(old_w);
	return (new_w);
}

char	*join_prefix(char *base, char *added, char *suffix)
{
	char	*tmp;
	char	*result;

	tmp = append_str(base, suffix);
	if (tmp == NULL)
		return (NULL);
	result = append_str(tmp, added);
	return (result);
}
