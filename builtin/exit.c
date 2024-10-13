/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 23:38:45 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/13 15:49:57 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_argc(t_command *command)
{
	size_t	i;

	i = 0;
	while (command->arguments[i])
		i++;
	return (i);
}

static int	check_size(char *str)
{
	if (!str)
		return (1);
	if (str[0] == '-')
	{
		if (ft_strlen(str) > 11)
			return (1);
		else if (ft_strlen(str) == 11 && ft_memcmp(str, "-2147483648", 11) > 0)
			return (1);
	}
	else
	{
		if (ft_strlen(str) > 10)
			return (1);
		else if (ft_strlen(str) == 10 && ft_memcmp(str, "2147483647", 11) > 0)
			return (1);
	}
	return (0);
}

int	ft_onlydigit(char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '-')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (1);
	while (i < ft_strlen(str))
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(t_minishell *minishell, t_command *command)
{
	if (get_argc(command) == 1)
		exit_shell(minishell, 0, true);
	if (get_argc(command) > 2)
	{
		ft_dprintf(2, "exit: too many arguments\n");
		minishell->exit_status = 1;
		return (1);
	}
	if (ft_onlydigit(command->arguments[1])
		|| check_size(command->arguments[1]))
	{
		ft_dprintf(2, "exit: %s: numeric argument required\n",
			command->arguments[1]);
		minishell->exit_status = 2;
		exit_shell(minishell, 2, false);
	}
	minishell->exit_status = (ft_atoi(command->arguments[1]) % 256);
	exit_shell(minishell, 0, true);
	return (0);
}

int	exit_shell(t_minishell *minishell, int exit_code, bool display)
{
	if (display)
		ft_putstr_fd("exit\n", 2);
	free_all_commands(minishell);
	free_env(minishell->env);
	exit(exit_code);
}
