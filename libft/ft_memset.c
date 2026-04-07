/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:28:00 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/18 11:07:27 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)b;
	i = 0;
	while (i < len)
		str[i++] = c;
	return (b);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     char str[50] = "GeeksForGeeks is for programming geeks.";
//     printf("\nBefore memset(): %s\n", str);
// 	char strr[50] = "GeeksForGeeks is for programming geeks.";

//     // Fill 8 characters starting from str[13] with '.'
//     memset(str + 13, '.', 8*sizeof(char));
// 	ft_memset(strr + 13, '.', 8*sizeof(char));

//     printf("After memset():  %s\n", str);
// 	printf("my function: %s\n", strr);
//     return 0;
// }

// int c -> which symbol we're printing
// size_t len -> how much c we're printing
// void *b -> flexible datatype