/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:53:29 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/17 19:47:10 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c +32);
	else
		return (c);
}

// int	main(void)
// {
// 	printf("%c\n", tolower(100));
// 	printf("%c\n", ft_tolower(100));
// 	return (0);
// }

// return ((c >= 65 && c <= 90) ? (c + 32) : c);