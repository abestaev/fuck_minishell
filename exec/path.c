/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:32:25 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/17 13:20:27 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**str_join_free(char **path);

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
	path = str_join_free(path);
	return (path);
}

static char	**str_join_free(char **path)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (path && path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = tmp;
		i++;
	}
	return (path);
}
