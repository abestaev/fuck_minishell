/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:31:34 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/09/01 16:25:48 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_equal(char *str)
{
	int	i;

	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')
			|| str[0] == '_'))
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	is_correct(char *str)
{
	int	i;

	if (is_equal(str))
		return (1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
				&& str[i] <= 'Z'))
			i++;
		else if (str[i] >= 0 && str[i] <= 9)
			i++;
		else if (str[i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_new_env(t_minishell *minishell, char *str)
{
	t_env	*new;
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	while (str[i] && str[i] != '=')
		i++;
	i++;
	new->key = malloc(i);
	if (!(new->key))
		return (free(new), 1);
	ft_strlcpy(new->key, str, i);
	value = malloc(ft_strlen(str) - i + 1);
	if (!value)
		return (free(new->key), free(new), 1);
	while (str[i])
		value[j++] = str[i++];
	value[j] = 0;
	new->value = value;
	return (ft_envadd_back(&minishell->env ,new) ,0);
}

int	ft_export(t_minishell *minishell, t_command *command)
{
	char	**tab;
	int		i;

	tab = command->arguments;
	i = 0;
	while (tab[i])
	{
		if (is_correct(tab[i]))
			ft_new_env(minishell,tab[i]);
		i++;
	}
	return (0);
}
