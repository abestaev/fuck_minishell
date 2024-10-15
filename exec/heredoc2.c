/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:20:52 by albestae          #+#    #+#             */
/*   Updated: 2024/10/15 18:27:00 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	link_heredoc(t_command *command)
{
	int	fd;

	fd = open(command->hd_filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open failed\n");
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 failed\n");
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	free(command->hd_filename);
	command->hd_filename = NULL;
	return (fd);
}

int	open_heredoc(t_command *command, t_minishell *mini)
{
	t_command	*tmp;
	t_redir		*tmp2;

	tmp = command;
	while (tmp)
	{
		tmp2 = tmp->redirections;
		while (tmp2)
		{
			if (tmp2->type == HEREDOC && g_signal_received != 92)
				read_heredoc(tmp, tmp2->file, mini);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	g_signal_received = 0;
	return (EXIT_SUCCESS);
}
