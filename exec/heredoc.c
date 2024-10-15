/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:23:53 by albestae          #+#    #+#             */
/*   Updated: 2024/10/15 17:06:28 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

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

int	read_heredoc(t_command *command, char *delimiter, t_minishell *mini)
{
	int		fd_hd;
	char	*line;
	int		pid;

	line = NULL;
	command->is_hd = TRUE;
	pid = fork();
	if (command->hd_filename)
	{
		unlink(command->hd_filename);
		free(command->hd_filename);
	}
	command->hd_filename = generate_name();
	if (pid == 0)
	{
		fd_hd = open(command->hd_filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
		while (1)
		{
			signal(SIGINT, ft_signal_heredoc);
			signal(SIGQUIT, SIG_IGN);
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
		exit_shell(mini, 0, false);
		return (EXIT_SUCCESS);
	}
	waitpid(pid, &g_signal_received, 0);
	if (WIFEXITED(g_signal_received))
		g_signal_received = WEXITSTATUS(g_signal_received);
	return (EXIT_SUCCESS);
}

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
			{
				read_heredoc(tmp, tmp2->file, mini);
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	g_signal_received = 0;
	return (EXIT_SUCCESS);
}
