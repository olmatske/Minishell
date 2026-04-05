/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:39:57 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/14 17:22:08 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *b, size_t len)
{
	ft_memset(b, 0, len);
}

// #include <strings.h>
// #include <stdio.h>
// int main()
// {
//     char str[50] = "GeeksForGeeks is for programming geeks.";
//     printf("\nBefore bzero(): %s\n", str);
// 	char strr[50] = "GeeksForGeeks is for programming geeks.";

//     // Fill 8 characters starting from str[13] with '.'
//     bzero(str + 0, 8*sizeof(char));
// 	ft_bzero(strr + 0, 8*sizeof(char));

//     printf("After bzero(): %s\n", str);
// 	printf("my function(): %s\n", strr);
//     return 0;
// }