/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:49:13 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/13 21:35:12 by albestae         ###   ########.fr       */
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
	(void)sig;
	g_signal_received = 1;
    write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
	rl_replace_line("", 0);
    rl_on_new_line();
	if (isatty(0))
	ft_putstr_fd("\n", 1);
    rl_redisplay();
}

void 	ft_signal_heredoc(void)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
