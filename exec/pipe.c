/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 06:58:54 by albestae          #+#    #+#             */
/*   Updated: 2024/10/17 19:48:37 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	piping(t_command *command, t_minishell *minishell)
{
	if (command->id < minishell->n_cmd - 1)
	{
		if (pipe(minishell->fd) == -1)
		{
			perror("pipe failed\n");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

int	connect_child(t_command *command, t_minishell *minishell)
{
	if (command->id > 0)
	{
		dup2(minishell->prev_fd[0], STDIN_FILENO);
		ft_close(&minishell->prev_fd[0]);
		ft_close(&minishell->prev_fd[1]);
	}
	if (command->id < minishell->n_cmd - 1)
	{
		dup2(minishell->fd[1], STDOUT_FILENO);
		ft_close(&minishell->fd[0]);
		ft_close(&minishell->fd[1]);
	}
	return (0);
}

int	connect_parent(t_command *command, t_minishell *minishell)
{
	if (command->id > 0)
	{
		ft_close(&minishell->prev_fd[0]);
		ft_close(&minishell->prev_fd[1]);
	}
	if (command->id < minishell->n_cmd - 1)
	{
		minishell->prev_fd[0] = minishell->fd[0];
		minishell->prev_fd[1] = minishell->fd[1];
	}
	return (0);
}

void	ft_close(int *fd)
{
	if (*fd > 0)
	{
		close(*fd);
	}
	*fd = -1;
}
