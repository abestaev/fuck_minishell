/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:56:18 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/17 13:25:03 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//todo changer le fd si le echo est dans une redirection

int	ft_is_n_flag(char *str)
{
	int	i;

	if (*str != '-')
		return (0);
	i = 1;
	while (str[i] == 'n' || str[i] == 'e')
		++i;
	return (!str[i]);
}

int	ft_flag(char **tab)
{
	int	i;

	i = 1;
	while (tab[i] && ft_is_n_flag(tab[i]))
		i++;
	return (i - 1);
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
		i += flag;
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
