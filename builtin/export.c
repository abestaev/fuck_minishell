/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:31:34 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/15 15:31:56 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// todo ajouter fonction pour modifier seulement la value si la key existe deja

int	is_equal(char *str)
{
	int	i;

	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')
			|| str[0] == '_'))
	{
		ft_dprintf(2, "export : '%s' not a valid identifier\n", str);
		return (1);
	}
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
		{
			ft_dprintf(2, "export : '%s' not a valid identifier\n", str);
			return (1);
		}
	}
	return (0);
}

int	ft_new_env(t_minishell *minishell, char *str)
{
	t_env	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	while (str[i] && str[i] != '=')
		i++;
	i++;
	new->key = ft_substr(str, j, i - 1);
	if (!(new->key))
		return (free(new), 1);
	new->value = malloc(ft_strlen(str) - i + 1);
	if (!new->value)
		return (free(new->key), free(new), 1);
	while (str[i])
		new->value[j++] = str[i++];
	new->value[j] = 0;
	new->next = NULL;
	return (ft_envadd_back(&minishell->env, new), 0);
}

int	ft_set_change_value(t_minishell *minishell, char *str)
{
	int		i;
	t_env	*copy_env;

	i = 0;
	while (str[i] != '=')
		i++;
	str[i] = 0;
	copy_env = minishell->env;
	while (copy_env)
	{
		if (ft_strcmp(copy_env->key, str) == 0)
		{
			if (ft_change_value(copy_env, str + i + 1))
				return (1);
			return (0);
		}
		copy_env = copy_env->next;
	}
	str[i] = '=';
	if (ft_new_env(minishell, str))
		return (ft_dprintf(2, "Error malloc new env\n"), 1);
	return (0);
}

int	ft_export(t_minishell *minishell, t_command *command)
{
	char	**tab;
	int		i;

	tab = command->arguments;
	i = 1;
	if (!tab[i])
		return (1);
	while (tab[i])
	{
		if (!is_correct(tab[i]))
		{
			if (ft_set_change_value(minishell, tab[i]))
				return (1);
		}
		i++;
	}
	return (0);
}
