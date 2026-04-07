/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:57:30 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/18 13:47:09 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*strr;

	i = 0;
	strr = (unsigned char *)str;
	while (i < n)
	{
		if (strr[i] == (unsigned char)c)
			return (&strr[i]);
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char str[] = "Hello arkness My Old Friend";
// 	printf("%s\n", memchr(str, 'D', 7));
// 	printf("%s\n", ft_memchr(str, 'D', 7));
// 	return (0);
// }