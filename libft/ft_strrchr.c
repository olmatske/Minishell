/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:55:44 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/19 20:50:25 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	int	len;

	len = ft_strlen(str);
	while (len >= 0)
	{
		if (str[len] == (char)c)
			return (&str[len]);
		len--;
	}
	return (NULL);
}

// char	*ft_strrchr(char *str, int c)
// {
// 	size_t	len;
// 	char	*strr;

// 	len = ft_strlen(str);
// 	strr = &str[len - 1];
// 	if (!str)
// 		return (NULL);
// 	if (c == '\0')
// 		return (0);
// 	while (len)
// 	{
// 		if (*strr == (char)c)
// 			return (strr);
// 		len--;
// 		strr--;
// 	}
// 	return (NULL);
// }

// int	main(void)
// {
// 	char str[5] = "FUCHK";
// 	printf("%s\n", ft_strrchr(str, 67));
// 	printf("%s\n", strrchr(str, 67));
// 	return (0);
// }

// alaways use the fucntions you already made