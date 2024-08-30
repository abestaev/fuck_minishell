/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:32:19 by ssitchsa          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/08/29 19:56:36 by ssitchsa         ###   ########.fr       */
=======
/*   Updated: 2024/08/30 16:16:14 by albestae         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run(t_command *command, t_minishell *minishell)
{
	int	status;
	int	last_status;

	while (command)
	{
		command->pid = fork();
		if (command->pid == -1)
		{
			ft_putstr_fd("fork failed\n", 2);
			return (1);
		}
		if (command->pid == 0)
		{
			if (is_builtin(command))
				exec_builtin(command, minishell);
			else if (exec_cmd(command, minishell))
			{
				ft_printf("%s: command not found\n", command->command);
				exit(1);
			}
		}
		else
		{
			waitpid(command->pid, &status, 0);
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
		}
		command = command->next;
	}
	return (last_status);
}

int	exec_cmd(t_command *cmd, t_minishell *minishell)
{
	size_t i;
	char *abs_path = "";

	if (ft_strchr(cmd->command, '/'))
		if (execve(cmd->command, cmd->arguments, minishell->env_tab))
			return (1);
	i = 0;
	while (minishell->path[i])
	{
		abs_path = ft_strjoin(minishell->path[i], cmd->command);
		execve(abs_path, cmd->arguments, minishell->env_tab);
		free(abs_path);
		i++;
	}
	return (1);
}