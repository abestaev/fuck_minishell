/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:56:18 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/09/03 20:26:40 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// todo	ori fraude pour les fd 1
int	ft_flag(char **tab)
{
	int	i;

	i = 1;
	if (!tab[i] || tab[i][0] != '-')
		return (0);
	i = 1;
	while (tab[1][i])
	{
		if (tab[1][i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_command *current)
{
	int		i;
	char	**tab;
	int		flag;

	i = 1;
	tab = current->arguments;
	if (!tab[i])
	{
		ft_putstr_fd("\n", 1);
		return (EXIT_SUCCESS);
	}
	flag = ft_flag(tab);
	if (flag)
		i++;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		if (tab[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}
