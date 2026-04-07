/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:01:03 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/18 14:25:04 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	count;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	count = ft_strlen(s);
	if (start >= count)
		return (ft_strdup(""));
	if (len > count - start)
		len = count - start;
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	while (i < len && s[start] != '\0')
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}

// int	main(void)
// {
// 	char s[] = "Hello there";
// 	int	start = 3;
// 	size_t	len = 5;
// }