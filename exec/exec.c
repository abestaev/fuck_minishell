/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:32:19 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/28 19:30:16 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//todo: exec une commande builtin (env)

int run(t_minishell *minishell)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        ft_putstr_fd("fork failed\n", 2);
        return (1);
    }
    if (pid == 0)
    {
        if (exec_cmd(minishell))
        {
            ft_putstr_fd("command not found\n", 2);
            exit(1);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
    }
    return (0);
}
int exec_cmd(t_minishell *minishell)
{
    size_t i;
    char    *abs_path = "";

    if (ft_strchr(minishell->command->command, '/'))
        if (execve(minishell->command->command, minishell->command->arguments, minishell->env_tab))
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