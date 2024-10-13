/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:23:59 by albestae          #+#    #+#             */
/*   Updated: 2024/10/13 17:03:39 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_append(t_command *command)
{
	int	fd;

	if (command->redirections->type == SINGLE_OUT)
		fd = open(command->redirections->file, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	else
		fd = open(command->redirections->file, O_WRONLY | O_CREAT | O_APPEND,
				0644);
	if (fd == -1)
		perror("open failed\n");
	return (fd);
}

int	get_outfile(t_command *command)
{
	int	fd;

	fd = check_append(command);
	if (fd == -1)
	{
		perror("open failed\n");
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 failed\n");
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int get_infile(t_command *command)
{
	int fd;
	fd = open(command->redirections->file, O_RDONLY);
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
	return (EXIT_SUCCESS);	
}

int	get_redir(t_command *command)
{
	t_command	*tmp;

	tmp = command;

	while (command->redirections)
	{
		if (command->redirections->type == SINGLE_OUT
			|| command->redirections->type == DOUBLE_OUT)
			get_outfile(command);
		else if (command->redirections->type == SINGLE_IN)
			get_infile(command);
		command->redirections = command->redirections->next;
	}
	if (command->is_hd)
		link_heredoc(command);
	command = tmp;
	return (EXIT_SUCCESS);
}
