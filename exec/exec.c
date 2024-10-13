/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:32:19 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/10 04:04:48 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wait(t_minishell *minishell);

int	run_single_cmd(t_command *command, t_minishell *minishell)
{
	open_heredoc(command);
	if (is_builtin(command))
	{
		get_redir(command);
		return (exec_builtin(command, minishell));
	}
	command->pid = fork();
	if (command->pid == -1)
	{
		ft_putstr_fd("fork failed\n", 2);
		return (1);
	}
	if (command->pid == 0)
	{
		get_redir(command);
		if (exec_cmd(command, minishell))
		{
			ft_printf("%s: command not found\n", command->command);
			minishell->exit_status = 127;
			exit_shell(minishell, 127, false);
		}
	}
	minishell->exit_status = ft_wait(minishell);
	return (0);
}

int	run(t_command *command, t_minishell *minishell)
{
	int	last_status;
	int	i;

	last_status = 0;
	i = 0;
	open_heredoc(command);
	while (command)
	{
		piping(command, minishell);
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
				exit(1);
			}
		}
		else
			connect_parent(command, minishell);
		signal(SIGINT, SIG_IGN);
		command = command->next;
		i++;
	}
	last_status = ft_wait(minishell);
	return (last_status);
}

static int	ft_wait(t_minishell *minishell)
{
	int	status;
	int	last_status;
	t_command *tmp;

	last_status = 0;
	tmp = minishell->command;
	while (tmp)
	{
		if (waitpid(tmp->pid, &status, 0) == -1)
		{
			perror("waitpid failed\n");
			return (1);
		}
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		tmp = tmp->next;
	}
	return (last_status);
}

int	exec_cmd(t_command *cmd, t_minishell *minishell)
{
	size_t	i;
	char	*abs_path;
	char	**path;
	char	**env;

	abs_path = "";
	path = get_path(minishell->env);
	env = env_to_tab(minishell->env);
	if (ft_strchr(cmd->command, '/'))
		if (execve(cmd->command, cmd->arguments, env))
			return (free_tab(path), free_tab(env), 0);

	i = 0;
	while (path[i])
	{
		abs_path = ft_strjoin(path[i], cmd->command);
		execve(abs_path, cmd->arguments, env);
		free(abs_path);
		i++;
	}
	return (free_tab(path), free_tab(env), 1);
}
