/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:03:50 by albestae          #+#    #+#             */
/*   Updated: 2024/08/30 23:17:38 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command *command)
{
	if (!ft_strcmp(command->command, "env"))
		return (1);
	else if (!ft_strcmp(command->command, "echo"))
		return (1);
	else if (!ft_strcmp(command->command, "cd"))
		return (1);
	/* if (!ft_strcmp(command->command, "export"))
		return (1);
	if (!ft_strcmp(command->command, "unset"))
		return (1);
	if (!ft_strcmp(command->command, "exit"))
		return (1);
	if (!ft_strcmp(command->command, "pwd"))
		return (1);*/
	return (0);
}

int	exec_builtin(t_command *command, t_minishell *minishell)
{
	if (!ft_strcmp(command->command, "env"))
		return (print_env(minishell));
	if (!ft_strcmp(command->command, "echo"))
		return (ft_echo(command));
	if (!ft_strcmp(command->command, "cd"))
        return (ft_cd(minishell, command));
	return (0);
}
