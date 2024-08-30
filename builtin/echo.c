/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:56:18 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/30 19:55:20 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//todo	ori fraude pour les fd 1 
int ft_flag(char **tab)
{
	int i;

	i = 0;
	while(tab[1])
	{
		if (tab[1][i++] != '-')
			return (0);
		while(tab[1][i])
		{
			if (tab[1][i] && tab[1][i] != 'n')
				return (0);
			i++;
		}
	}
	return (1);
}

int	ft_echo(t_command *current)
{
	int	i;
	char **tab;
	int flag;
	
	i = 1;
	flag = 0;
	tab = current->arguments;
	if (!current)
		return (1);
	flag = ft_flag(tab);
	if (flag)
		i++;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		if (tab[i] && tab[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (flag == 1)
	{
		printf("oui");
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
