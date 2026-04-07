/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:26:02 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/17 19:00:50 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)

{
	return (c >= 0 && c <= 127);
}

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%d\n", ft_isascii(123));
// 	return (0);
// }