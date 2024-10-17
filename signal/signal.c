/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:49:13 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/17 16:27:28 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t			g_signal_received = 0;

t_minishell	*starton(void)
{
	static t_minishell	mini = {0};

	return (&mini);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
		g_signal_received = sig;
	}
}

void	ft_signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_received = 1;
		close(0);
	}
}

void	ft_signal(t_minishell *shell)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	if (shell->old_fd[0])
	{
		dup2(shell->old_fd[0], 0);
		ft_close(&shell->old_fd[0]);
	}
	if (shell->old_fd[1])
	{
		dup2(shell->old_fd[1], 1);
		ft_close(&shell->old_fd[1]);
	}
	shell->old_fd[0] = dup(0);
	shell->old_fd[1] = dup(1);
}
