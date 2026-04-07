/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:11:30 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/23 17:12:10 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_wordcount(char const *str, char c);
static int		ft_tokenize(char const *str, char c, char **res);
static void		ft_free(char **res);

char	**ft_split(char const *s, char c)
{
	char	**res;

	res = ft_calloc(ft_wordcount(s, c) + 1, sizeof(char *));
	if (!res)
		return (NULL);
	if (ft_tokenize(s, c, res) == -1)
	{
		ft_free(res);
		return (NULL);
	}
	return (res);
}

static int	ft_wordcount(char const *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			continue ;
		}
		word++;
		while (str[i] != c && str[i])
			i++;
	}
	return (word);
}

static int	ft_tokenize(char const *str, char c, char **res)
{
	int		i;
	int		k;
	int		w;

	i = 0;
	k = 0;
	w = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			k = 0;
			continue ;
		}
		while (str[i] != c && str[i])
		{
			i++;
			k++;
		}
		res[w] = ft_substr(str, i - k, k);
		if (!res[w++])
			return (-1);
	}
	return (0);
}

static void	ft_free(char **res)
{
	int	w;

	w = 0;
	while (res[w])
	{
		free(res[w]);
		w++;
	}
	free(res);
}

// int	main(void)
// {
// 	char	str[] = "Hello Bitch I love marshmallows";
// 	printf("%s\n", ft_split(str, ' ')[1]);
// 	return (0);
// }