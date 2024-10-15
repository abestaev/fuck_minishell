/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:32:19 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/15 18:19:51 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	antislash(int sig)
{
	if (sig == SIGQUIT)
		exit(131);
	if (sig == SIGINT)
		exit(130);
}

int			get_redir_builtin(t_command *command);

int	fork_and_execute(t_command *command, t_minishell *minishell)
{
	command->pid = fork();
	if (command->pid == -1)
	{
		ft_putstr_fd("fork failed\n", 2);
		return (1);
	}
	if (command->pid == 0)
	{
		signal(SIGINT, &signal_handler);
		signal(SIGQUIT, &antislash);
		get_redir(command);
		if (exec_cmd(command, minishell))
		{
			minishell->exit_status = 127;
			exit_shell(minishell, 127, false);
		}
		exit_shell(minishell, 0, true);
	}
	return (0);
}

int	run_single_cmd(t_command *command, t_minishell *minishell)
{
	open_heredoc(command, minishell);
	if (is_builtin(command))
	{
		if (get_redir_builtin(command))
			return (1);
		return (exec_builtin(command, minishell));
	}
	signal(SIGINT, SIG_IGN);
	if (fork_and_execute(command, minishell))
		return (1);
	signal(SIGQUIT, SIG_IGN);
	minishell->exit_status = ft_wait(minishell);
	return (minishell->exit_status);
}

int	ft_wait(t_minishell *minishell)
{
	int			last_status;
	t_command	*tmp;

	last_status = 0;
	tmp = minishell->command;
	while (tmp)
	{
		if (waitpid(tmp->pid, &minishell->exit_status, 0) == -1)
		{
			perror("waitpid failed\n");
			return (1);
		}
		if (WIFEXITED(minishell->exit_status))
			minishell->exit_status = WEXITSTATUS(minishell->exit_status);
		tmp = tmp->next;
	}
	return (minishell->exit_status);
}

int	exec_cmd(t_command *cmd, t_minishell *minishell)
{
	size_t	i;
	char	*abs_path;
	char	**path;
	char	**env;

	abs_path = "";
	if (!cmd->command)
		return (0);
	path = get_path(minishell->env);
	env = env_to_tab(minishell->env);
	if (ft_strchr(cmd->command, '/'))
		if (execve(cmd->command, cmd->arguments, env))
			return (free_tab(path), free_tab(env), 1);
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
