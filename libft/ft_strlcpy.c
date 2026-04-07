/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:46:40 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/18 11:00:09 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] && i < dstsize - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

// int	main(void)
// {
// 	char	src[] = "Hello World";
// 	char	dest[10] = "";
// 	char	s[] = "Hello World";
// 	char	d[10] = "";
// 	printf("%zu\n", strlcpy(dest, src, 5));
// 	printf("%zu\n", ft_strlcpy(d, s, 5));
// 	return (0);
// }
