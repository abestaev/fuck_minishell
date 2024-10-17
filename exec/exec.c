/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:32:19 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/17 20:38:07 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redir_builtin(t_command *command);

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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_close(&minishell->old_fd[0]);
		ft_close(&minishell->old_fd[1]);
		get_redir(command);
		exec_cmd(command, minishell);
		exit_shell(minishell, 0);
	}
	return (0);
}

int	run_single_cmd(t_command *command, t_minishell *minishell)
{
	if (open_heredoc(command, minishell))
		return (130);
	g_signal_received = 0;
	if (is_builtin(command))
	{
		if (get_redir_builtin(command))
			return (1);
		return (exec_builtin(command, minishell));
	}
	if (fork_and_execute(command, minishell))
		return (1);
	minishell->exit_status = ft_wait(minishell);
	return (minishell->exit_status);
}

int	ft_wait(t_minishell *minishell)
{
	t_command	*tmp;

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
		if (WIFSIGNALED(minishell->exit_status))
		{
			if (WTERMSIG(minishell->exit_status) == SIGINT)
				minishell->exit_status = 130;
			if (WTERMSIG(minishell->exit_status) == SIGQUIT)
			{
				ft_dprintf(2, "Quit (core dumped)\n");
				minishell->exit_status = 131;
			}
		}
		tmp = tmp->next;
	}
	return (minishell->exit_status);
}

int	exec_path_cmd(t_command *cmd, t_minishell *minishell, char **env,
		char **path)
{
	struct stat	stats;

	if (access(cmd->command, F_OK))
	{
		ft_dprintf(2, "minishell: %s: No such file or directory\n",
			cmd->command);
		return (free_tab(path), free_tab(env), exit_shell(minishell, 127), 1);
	}
	if (!stat(cmd->command, &stats) && S_ISDIR(stats.st_mode))
	{
		ft_dprintf(2, "minishell: %s: Is a directory\n", cmd->command);
		return (free_tab(path), free_tab(env), exit_shell(minishell, 126), 1);
	}
	if (access(cmd->command, R_OK) || access(cmd->command, X_OK))
	{
		ft_dprintf(2, "minishell: %s: Permission denied\n", cmd->command);
		return (free_tab(path), free_tab(env), exit_shell(minishell, 126), 1);
	}
	execve(cmd->command, cmd->arguments, env);
	return (free_tab(path), free_tab(env), exit_shell(minishell, 126), 1);
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
		exec_path_cmd(cmd, minishell, env, path);
	i = 0;
	while (path && path[i])
	{
		abs_path = ft_strjoin(path[i], cmd->command);
		execve(abs_path, cmd->arguments, env);
		free(abs_path);
		i++;
	}
	ft_printf("minishell: %s: command not found\n", cmd->command);
	return (free_tab(path), free_tab(env), exit_shell(minishell, 127), 1);
}
