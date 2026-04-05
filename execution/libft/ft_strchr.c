/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:59:28 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/18 15:15:05 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str && *str != (char)c)
		(str)++;
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}

// int	main(void)
// {
// 	// char str[] = "Creeper, Aww Man!";
// 	// printf("%s\n", strchr(str, 44)); // 44 is ,
// 	printf("%s\n", ft_strchr("teste", 0));
// 	return (0);
// }
