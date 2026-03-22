/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_about_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:50:26 by anshuval          #+#    #+#             */
/*   Updated: 2026/03/22 19:52:28 by anshuval         ###   ########.fr       */
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

