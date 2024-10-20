/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:23:59 by albestae          #+#    #+#             */
/*   Updated: 2024/10/17 22:12:41 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_append(t_redir *redir)
{
	int	fd;

	if (redir->type == SINGLE_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		perror("open failed\n");
	return (fd);
}

int	get_outfile(t_redir *file)
{
	int	fd;

	fd = check_append(file);
	if (fd == -1)
	{
		perror("open failed\n");
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 failed\n");
		ft_close(&fd);
		return (EXIT_FAILURE);
	}
	ft_close(&fd);
	return (EXIT_SUCCESS);
}

int	get_infile(t_redir *file)
{
	int	fd;

	if (access(file->file, F_OK) == -1)
	{
		ft_dprintf(2, "minishell: %s: No such file or directory\n", file->file);
		return (EXIT_FAILURE);
	}
	fd = open(file->file, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(2, "minishell : %s ", file->file);
		perror("");
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 failed\n");
		ft_close(&fd);
		return (EXIT_FAILURE);
	}
	ft_close(&fd);
	return (EXIT_SUCCESS);
}

int	get_redir(t_command *command)
{
	t_redir	*tmp;

	tmp = command->redirections;
	while (tmp)
	{
		if (tmp->type == SINGLE_OUT || tmp->type == DOUBLE_OUT)
		{
			if (get_outfile(tmp))
				exit_shell(command->minishell, 2);
		}
		else if (tmp->type == SINGLE_IN)
		{
			if (get_infile(tmp))
				exit_shell(command->minishell, 2);
		}
		tmp = tmp->next;
	}
	if (command->is_hd)
		link_heredoc(command);
	return (EXIT_SUCCESS);
}

int	get_redir_builtin(t_command *command)
{
	t_redir	*tmp;

	tmp = command->redirections;
	while (tmp)
	{
		if (tmp->type == SINGLE_OUT || tmp->type == DOUBLE_OUT)
		{
			if (get_outfile(tmp))
				return (EXIT_FAILURE);
		}
		else if (tmp->type == SINGLE_IN)
		{
			if (get_infile(tmp))
				return (EXIT_FAILURE);
		}
		tmp = tmp->next;
	}
	if (command->is_hd)
		link_heredoc(command);
	return (EXIT_SUCCESS);
}
