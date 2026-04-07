/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:46:20 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/23 17:11:35 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n);

char	*ft_itoa(int n)
{
	long	num;
	int		i;
	int		check;
	char	*res;

	num = n;
	check = 0;
	if (num < 0)
		check++;
	i = ft_count(n) + check;
	res = ft_calloc(i-- + 1, sizeof(char));
	if (!res)
		return (NULL);
	if (check == 1)
		num = -num;
	while (num > 9)
	{
		res[i--] = (num % 10) + '0';
		num /= 10;
	}
	if (num < 10)
		res[i--] = num + '0';
	if (check == 1)
		res[0] = '-';
	return (res);
}

static int	ft_count(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

// int	main(void)
// {
// 	// int	nb = -145879;
// 	printf("%s\n", ft_itoa(1));
// 	printf("%s\n", ft_itoa(2464574));
// 	printf("%s\n", ft_itoa(-1));
// 	printf("%s\n", ft_itoa(-2464574));
// printf("%s\n", ft_itoa(-2147483648));
// 	printf("%s\n", ft_itoa(0));
	// return (0);
// }
