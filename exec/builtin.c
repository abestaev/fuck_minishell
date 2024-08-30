/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:03:50 by albestae          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/08/29 20:27:15 by ssitchsa         ###   ########.fr       */
=======
/*   Updated: 2024/08/30 16:18:29 by albestae         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(t_command *command)
{
    if (!ft_strcmp(command->command, "env"))
        return (1);
<<<<<<< Updated upstream
    // else if (!ft_strcmp(command->command, "echo"))
    //     return (1);
=======
    /*if (!ft_strcmp(command->command, "echo"))
        return (1);
    if (!ft_strcmp(command->command, "cd"))
        return (1);
    if (!ft_strcmp(command->command, "export"))
        return (1);
    if (!ft_strcmp(command->command, "unset"))
        return (1);
    if (!ft_strcmp(command->command, "exit"))
        return (1);
    if (!ft_strcmp(command->command, "pwd"))
        return (1);*/   
>>>>>>> Stashed changes
    return (0);
}

int exec_builtin(t_command *command, t_minishell *minishell)
{
    if (!ft_strcmp(command->command, "env"))
        return (print_env(minishell));
<<<<<<< Updated upstream
    else if (!ft_strcmp(command->command, "echo"))
        return (ft_echo(minishell, command));
=======
    if (!ft_strcmp(command->command, "echo"))
        return (ft_echo(minishell));
    if (!ft_strcmp(command->command, "cd"))
    
>>>>>>> Stashed changes
    return (0);
}
