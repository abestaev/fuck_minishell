/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:32:19 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/29 19:56:36 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pipeline(t_minishell *minishell)
{
    t_command *command;

    command = minishell->command;
    while (command)
    {
        if (is_builtin(command))
            exec_builtin(command, minishell);
        else
            run(command, minishell);
        command = command->next;
    }
}

int	run(t_command *command, t_minishell *minishell)
{
	int		status;
    
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
            else
                if (exec_cmd(minishell))
                {
                    ft_printf("%s: command not found\n", minishell->command->command);
                    exit(1);
                }
	    }
        else
	    {
            waitpid(command->pid, &status, 0);
            if (WIFEXITED(status))
                return (WEXITSTATUS(status));
	    }
        command = command->next;
    }
	return (0);
}

int	exec_cmd(t_minishell *minishell)
{
	size_t i;
	char *abs_path = "";

	if (ft_strchr(minishell->command->command, '/'))
		if (execve(minishell->command->command, minishell->command->arguments,
				minishell->env_tab))
			return (1);
	i = 0;
	while (minishell->path[i])
	{
		abs_path = ft_strjoin(minishell->path[i], minishell->command->command);
		execve(abs_path, minishell->command->arguments, minishell->env_tab);
		free(abs_path);
		i++;
	}
	return (1);
}