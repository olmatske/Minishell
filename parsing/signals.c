/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshuval <anshuval@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:48:33 by anshuval          #+#    #+#             */
/*   Updated: 2026/05/31 14:01:52 by anshuval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// prints a newline, prompts anew, clears the buffer, stores the signal exit
// status to 130
static void	handle_sigint(int sig)
{
	(void)sig;
	g_signal = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// ctrl+C instead of killing the programm is substituted by handle_sigint
// ctrl+\ instead of killing the program does nothing
// ctrl+z instead of killing the program does nothing
void	replace_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
