/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:23:53 by albestae          #+#    #+#             */
/*   Updated: 2024/10/17 16:31:55 by ssitchsa         ###   ########.fr       */
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

void	read_lines(int fd_hd, char *delimiter, t_minishell *mini)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, ft_signal_heredoc);
		signal(SIGQUIT, SIG_IGN);
		line = readline("\033[3;34mheredoc> \033[0m");
		if (g_signal_received)
		{
			ft_close(&fd_hd);
			exit_shell(mini, 1);
		}
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd_hd);
		free(line);
	}
}

void	handle_heredoc_child(t_command *command, char *delimiter,
		t_minishell *mini)
{
	int	fd_hd;

	fd_hd = open(command->hd_filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	read_lines(fd_hd, delimiter, mini);
	ft_close(&fd_hd);
	exit_shell(mini, 0);
}

void	prepare_heredoc_file(t_command *command)
{
	if (command->hd_filename)
	{
		unlink(command->hd_filename);
		free(command->hd_filename);
	}
	command->hd_filename = generate_name();
}

int	read_heredoc(t_command *command, char *delimiter, t_minishell *mini)
{
	int	pid;
	int	status;

	command->is_hd = TRUE;
	prepare_heredoc_file(command);
	pid = fork();
	if (pid == 0)
		handle_heredoc_child(command, delimiter, mini);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}
