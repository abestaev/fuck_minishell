/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:04:08 by albestae          #+#    #+#             */
/*   Updated: 2024/10/17 13:30:16 by albestae         ###   ########.fr       */
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
		connect_child(command, minishell);
		get_redir(command);
		if (is_builtin(command))
			exit(exec_builtin(command, minishell));
		else if (exec_cmd(command, minishell))
		{
			ft_printf("%s: command not found\n", command->command);
			free_all_commands(minishell);
			free_env(minishell->env);
			exit(127);
		}
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
		signal(SIGINT, SIG_IGN);
		command = command->next;
	}
	return (0);
}

int	run(t_command *command, t_minishell *minishell)
{
	int	last_status;

	open_heredoc(command, minishell);
	signal(SIGINT, SIG_IGN);
	if (execute_commands(command, minishell))
		return (1);
	last_status = ft_wait(minishell);
	return (last_status);
}
