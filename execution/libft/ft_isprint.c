/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 01:04:53 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/17 19:00:59 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%d\n", ft_isprint(2));
// 	return(0);
// }
// 1 true
// 0 false
// 'xyz' is character itself, not in '' is ascii value