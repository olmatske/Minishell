/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:59:28 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/23 17:14:33 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	k;
	void	*ptr;

	k = count * size;
	ptr = (void *)malloc(k);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, k);
	return (ptr);
}

// int	main(void)
// {
// 	size_t count = 3;
// 	size_t size = 4;
// }