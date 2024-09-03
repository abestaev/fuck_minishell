/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:23:53 by albestae          #+#    #+#             */
/*   Updated: 2024/09/03 18:02:57 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_name(void)
{
	static int	i;
	char		*filename;
	char		*num;

	num = ft_itoa(i);
	i++;
	if (!num)
	{
		perror("itoa failed\n");
		return (NULL);
	}
	filename = ft_strjoin("/tmp/heredoc_", num);
	if (!filename)
	{
		perror("strjoin failed\n");
		return (NULL);
	}
	free(num);
	return (filename);
}

int	read_heredoc(t_command *command, char *delimiter)
{
	int fd_hd;
	char *line = NULL;

	command->is_hd = TRUE;
	if (command->hd_filename)
	{
		unlink(command->hd_filename);
		free(command->hd_filename);
	}
	command->hd_filename = generate_name();
	fd_hd = open(command->hd_filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("\033[3;34mheredoc> \033[0m");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		else
		{
			ft_putendl_fd(line, fd_hd);
			free(line);
		}
	}
	close(fd_hd);
	return (EXIT_SUCCESS);
}

int check_heredoc(t_command *command)
{
	int fd;

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
	return (fd);
}