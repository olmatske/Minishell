/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:42:46 by olmatske          #+#    #+#             */
/*   Updated: 2026/05/30 23:08:32 by olmatske         ###   ########.fr       */
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

char	*gc_strdup(t_shell *shell, const char *s1)
{
	size_t	size;
	size_t	i;
	char	*ptr;

	i = 0;
	size = ft_strlen(s1);
	ptr = gc_malloc(shell, sizeof(char) * (size + 1));
	if (!ptr)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*gc_strjoin(t_shell *shell, char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*res;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = gc_malloc(shell, sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return (NULL);
	if (s1)
		ft_strlcpy(res, s1, len1 + 1);
	if (s2)
		ft_strlcpy(res + len1, s2, len2 + 1);
	return (res);
}

int	isnumstr(const char *str)
{
	if (!str || !str[0])
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*(unsigned char *)str))
			return (0);
		str++;
	}
	return (1);
}

void	free_all(t_shell *shell, t_env **env, t_cmd_node *cmd)
{
	(void)env;
	if (cmd)
		free_cmd_list(cmd);
	if (shell)
		gc_free_all(shell);
	if (shell)
		free(shell);
}
