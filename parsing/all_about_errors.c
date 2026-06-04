/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_about_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:24:03 by anshuval          #+#    #+#             */
/*   Updated: 2026/06/04 22:04:31 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_error(char *s, int exit_code)
{
	ft_putstr_fd(s, STDERR_FILENO);
	exit(exit_code);
}

void	ft_perror(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	print_quote_warning(char *line)
{
	int		in_single;
	int		in_double;
	int		i;

	in_single = NO;
	in_double = NO;
	i = 0;
	while (line && line[i])
	{
		quote_status(line[i], &in_double, &in_single);
		i++;
	}
	ft_putstr_fd(C_RED"Bashtard: unexpected EOF while looking "
		"for matching `", 2);
	if (in_double)
		ft_putchar_fd('\"', 2);
	if (in_single)
		ft_putchar_fd('\'', 2);
	ft_putstr_fd("'\nBashtard: syntax error: unexpected end of file\n"R, 2);
}
