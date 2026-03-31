/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_about_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:24:03 by anshuval          #+#    #+#             */
/*   Updated: 2026/03/31 17:15:37 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

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
