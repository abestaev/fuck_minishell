/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:49:13 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/11 22:43:24 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal_received = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_received = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	if (isatty(0))
		ft_putstr_fd("\n", 1);
	rl_redisplay();
}

void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
	}
}

void	ft_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
