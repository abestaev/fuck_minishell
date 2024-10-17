/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 23:38:45 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/17 15:25:34 by ssitchsa         ###   ########.fr       */
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

static long	ft_atoi_safe(const char *str)
{
	long	n;
	long	sign;

	n = 0L;
	sign = 1L;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		++str;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1L;
		++str;
	}
	if (!(*str))
		return (INT_MAX + 1L);
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + (*str - '0');
		if (n > INT_MAX || n < INT_MIN)
			return (INT_MAX + 1L);
		++str;
	}
	if (*str)
		return (INT_MAX + 1L);
	return (n * sign);
}

int	ft_exit(t_minishell *minishell, t_command *command)
{
	long	n;

	if (minishell->n_cmd == 1)
		ft_dprintf(2, "exit\n");
	if (!command->arguments || !command->arguments[1])
		exit_shell(minishell, minishell->exit_status);
	n = ft_atoi_safe(command->arguments[1]);
	if (command->arguments && command->arguments[1]
		&& (n < INT_MIN || n > INT_MAX))
	{
		ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
			command->arguments[1]);
		minishell->exit_status = 2;
		exit_shell(minishell, 2);
	}
	if (get_argc(command) > 2)
	{
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		minishell->exit_status = 1;
		return (1);
	}
	minishell->exit_status = n;
	exit_shell(minishell, minishell->exit_status);
	return (0);
}

int	exit_shell(t_minishell *minishell, int exit_code)
{
	ft_close(&minishell->old_fd[0]);
	ft_close(&minishell->old_fd[1]);
	free_all_commands(minishell);
	free_env(minishell->env);
	exit(exit_code);
}
