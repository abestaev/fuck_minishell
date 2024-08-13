/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:32:25 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/12 18:29:47 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(t_list *env)
{
	t_list	*tmp;
	char	**path;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(((t_env *)tmp->content)->name, "PATH", 4))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	path = ft_split(((t_env *)tmp->content)->value, ':');
	return (path);
}

// path = match_env("path",minishell)
// r_path = path.value
