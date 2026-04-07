/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmatske <olmatske@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:18:42 by olmatske          #+#    #+#             */
/*   Updated: 2025/07/19 23:43:49 by olmatske         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = ft_strlen(s1);
	while (s1[i] && ft_strrchr((char *)set, s1[i]))
		i++;
	while (i < k && s1[k - 1] && ft_strrchr((char *)set, s1[k - 1]))
		k--;
	return (ft_substr(s1, i, k - i));
}
// use strchr and strrchr!!!
