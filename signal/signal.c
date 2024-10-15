/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:49:13 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/15 05:41:58 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal_received = 0;

void signal_handler(int sig)
{
    if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

void ft_signal_heredoc(int sig)
{
    if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_dprintf(STDERR_FILENO, "\n");
		exit(130);
	}
}

void ft_signal(void)
{
    signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
