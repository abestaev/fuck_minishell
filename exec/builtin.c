/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:03:50 by albestae          #+#    #+#             */
/*   Updated: 2024/08/29 16:03:56 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(t_command *command)
{
    if (!ft_strcmp(command->command, "env"))
        return (1);
    return (0);
}

int exec_builtin(t_command *command, t_minishell *minishell)
{
    if (!ft_strcmp(command->command, "env"))
        return (print_env(minishell));
    return (0);
}