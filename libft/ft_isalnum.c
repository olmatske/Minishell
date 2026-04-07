/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:55:23 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/06 01:03:37 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int i)

{
	return (ft_isalpha(i) || ft_isdigit(i));
}

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%d\n", ft_isalnum('5'));
// 	return (0);
// }