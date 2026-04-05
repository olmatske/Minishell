/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:03:10 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/18 11:22:56 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	i = 0;
	if (destsize <= dlen)
		return (destsize + slen);
	while (src[i] && dlen + i < destsize - 1)
	{
		dest[dlen + i] = src[i];
		i++;
	}
	dest[dlen + i] = '\0';
	return (dlen + slen);
}

// int	main(void)
// {
// 	char dest[20] = "Hello there";
// 	char src[20] = "Creeper Aww Man";
// 	char d[20] = "Hello there";
// 	char s[20] = "Creeper Aww Man";
// 	printf("%lu\n", strlcat(d, s, 20));
// 	printf("%zu\n", ft_strlcat(dest, src, 20));
// 	return (0);
// }
// // return (detsize + k || k + i)