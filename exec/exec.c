/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:32:19 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/09/04 13:11:40 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wait(t_minishell *minishell);

static int	piping(t_command *command, t_minishell *minishell)
{
	if (command->id < minishell->n_cmd - 1)
	{
		if (pipe(minishell->fd) == -1)
		{
			perror("pipe failed\n");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

static int	connect_child(t_command *command, t_minishell *minishell)
{
	if (command->id > 0)
	{
		dup2(minishell->prev_fd[0], STDIN_FILENO);
		close(minishell->prev_fd[0]);
		close(minishell->prev_fd[1]);
	}
	if (command->id < minishell->n_cmd - 1)
	{
		dup2(minishell->fd[1], STDOUT_FILENO);
		close(minishell->fd[0]);
		close(minishell->fd[1]);
	}
	return (0);
}

static int	connect_parent(t_command *command, t_minishell *minishell)
{
	if (command->id > 0)
	{
		close(minishell->prev_fd[0]);
		close(minishell->prev_fd[1]);
	}
	if (command->id < minishell->n_cmd - 1)
	{
		minishell->prev_fd[0] = minishell->fd[0];
		minishell->prev_fd[1] = minishell->fd[1];
	}
	return (0);
}

int	run_single_cmd(t_command *command, t_minishell *minishell)
{
	int last_status;

	last_status = 0;
	if (is_builtin(command))
	{
		get_redir(command);
		exec_builtin(command, minishell);
		return (0);
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
			free_all_commands(minishell);
			free_env(minishell->env);
			exit(1);
		}
	}
	last_status = ft_wait(minishell);
	return (0);
}

int	run(t_command *command, t_minishell *minishell)
{
	int	last_status;
	int	i;

	last_status = 0;
	i = 0;
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
