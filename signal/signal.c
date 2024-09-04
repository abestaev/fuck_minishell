/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:49:13 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/09/03 21:48:21 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t		g_exit_status;
// int				g_signal_received;
void	sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	rl_on_new_line();
	if (isatty(0))
		ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}
// void 	signal_handler_heredoc(int signum)
// {
// 	g_signal_received = signum;
// 	if (signum == SIGINT)
// 	{
// 		g_signal_received = 2;
// 	}
// }

void	ft_signal(void)
{
	// signal(SIGINT, signal_handler_heredoc);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
