/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojak <wojak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 01:29:33 by wojak             #+#    #+#             */
/*   Updated: 2024/07/26 02:24:07 by wojak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    return (0);
}