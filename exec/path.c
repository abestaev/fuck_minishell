/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:32:25 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/28 19:29:23 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char     **str_join_free(char **path);

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

static char     **str_join_free(char **path)
{
    size_t  i;
    char    *tmp;

    i = 0;
    while (path[i])
    {
        tmp = ft_strjoin(path[i], "/");
        free(path[i]);
        path[i] = tmp;
        i++;
    }
    return (path);
}
// path = match_env("path",minishell)
// r_path = path.value
