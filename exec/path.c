/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojak <wojak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 01:29:30 by wojak             #+#    #+#             */
/*   Updated: 2024/07/26 02:18:23 by wojak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char     **str_join_free(char **path);

char    **get_path(t_list *env)
{
    t_list  *tmp;
    char    **path;
    
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