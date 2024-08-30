/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:32:19 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/30 20:46:27 by ssitchsa         ###   ########.fr       */
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
				free_all_commands(minishell);
				free_env(minishell->env);
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
	char **path;
	char **env;

	path = get_path(minishell->env);
	env = env_to_tab(minishell->env);
	if (ft_strchr(cmd->command, '/'))
		if (execve(cmd->command, cmd->arguments, env))
		{
			free_tab(path);
			free_tab(env);
			free(abs_path);
			return (1);
		}
	i = 0;
	while (path[i])
	{
		abs_path = ft_strjoin(path[i], cmd->command);
		execve(abs_path, cmd->arguments, env);
		free(abs_path);
		i++;
	}
	free_tab(path);
	free_tab(env);
	return (1);
}
