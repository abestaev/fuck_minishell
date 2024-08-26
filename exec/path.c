/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:32:25 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/26 20:07:41 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(t_env *env)
{
	t_env	*tmp;
	char	**path;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PATH", 4))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	path = ft_split(tmp->value, ':');
	return (path);
}

// path = match_env("path",minishell)
// r_path = path.value
