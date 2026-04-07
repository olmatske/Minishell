/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:26:21 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/18 15:44:32 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*a;
	char	*b;

	if (!dest && !src)
		return (NULL);
	i = 0;
	a = (char *)dest;
	b = (char *)src;
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (dest);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char dest[20] = "Hello there";
// 	char src[20] = "I'm a creeper";
// 	printf("%s\n", ft_memcpy(dest, src, 5));
// 	return (0);
// }

// void does not return
// void */ pointer function returns a pointer (to char in htis instance)