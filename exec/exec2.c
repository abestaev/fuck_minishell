/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:04:08 by albestae          #+#    #+#             */
/*   Updated: 2024/10/17 19:50:49 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_child_process(t_command *command, t_minishell *minishell)
{
	command->pid = fork();
	if (command->pid == -1)
	{
		ft_putstr_fd("fork failed\n", 2);
		return (1);
	}
	if (command->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_close(&minishell->old_fd[0]);
		ft_close(&minishell->old_fd[1]);
		connect_child(command, minishell);
		get_redir(command);
		if (is_builtin(command))
			exit_shell(minishell, exec_builtin(command, minishell));
		exec_cmd(command, minishell);
	}
	else
		connect_parent(command, minishell);
	return (0);
}

int	execute_commands(t_command *command, t_minishell *minishell)
{
	while (command)
	{
		piping(command, minishell);
		if (execute_child_process(command, minishell))
			return (1);
		command = command->next;
	}
	return (0);
}

int	run(t_command *command, t_minishell *minishell)
{
	int	last_status;

	if (open_heredoc(command, minishell))
		return (130);
	if (execute_commands(command, minishell))
		return (1);
	last_status = ft_wait(minishell);
	return (last_status);
}
