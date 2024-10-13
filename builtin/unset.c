/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:31:58 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/13 15:49:17 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lst_remove(t_minishell *minishell, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = minishell->env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				minishell->env = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

int	ft_unset(t_minishell *minishell, t_command *command)
{
	int	i;

	i = 1;
	while (command->arguments[i])
	{
		lst_remove(minishell, command->arguments[i]);
		i++;
	}
	minishell->exit_status = 0;
	return (0);
}
